**Instructions:**

**definitions:**
- `codefolder` matches regex `[0-9]{2}_[0-9]{3}_\S*`

- See the attached makefile and check that it follows this pseudo-code.
- point out any discrepancy.

- **Most IMPORTANT QUESTION:** Does it fit for purpose?
  - build projects in each `codefolder`
  - substitute `_defaults/nmi_handler` as necessary
  - substitute `_defaults/startup` as necessary
  - compile and link correctly

- **Do not** read comments
- **Do not** modify comments


**makefile defines:**
```
SDAS			:= sdasz80
SDCC			:= sdcc
SDOBJCOPY := sdobjcopy
Z80DASM		:= z80dasm

ASMFLAGS	:= -l
CFLAGS		:= -mz80 --std c99 -I_headers --Werror
#COPTFLAGS := --no-peep --nooverlay --nogcse --nolospre --nogenconstprop --nolabelopt --noinvariant --noinduction --noloopreverse --nostdlibcall
COPTFLAGS :=
LDFLAGS		:= -mz80 --no-std-crt0
DASMFLAGS := -a -l -t -g0

GREP := grep -E
RM := rm -f
CP := cp
```

**For `_defaults` folder:**
	```
	%.rel: %.s
		$(SDAS) $(ASMFLAGS) -o $@ $<

	%.rel: %.c
		$(SDCC) $(CFLAGS) -c $< -o $@
	```

**For each `codefolder`:**

	0 call the folder `$(1)`.

	1 Sources Check --bomb if `*.c`, `*.s`, or `*.rel_` doesn't exist
		```
		$(1)_CSRCS   := $(wildcard $(1)/*.c)
		$(1)_ASRCS   := $(wildcard $(1)/*.s)
		$(1)_RELSRCS := $(wildcard $(1)/*.rel_)
		```
	1.1 Convert Source Lists to object lists:
			```
			$(1)_COMPILED_RELS := $$(patsubst %.c, %.rel, $$($(1)_CSRCS))
			$(1)_ASM_RELS      := $$(patsubst %.s, %.rel, $$($(1)_ASRCS))
			$(1)_COPIED_RELS   := $$(patsubst %.rel_, %.rel, $$($(1)_RELSRCS))
			```
	1.2 Compile C sources (and delete built-$(1) file)
			```
			$$($(1)_COMPILED_RELS): %.rel: %.c
				$$(RM) built-$(1)
				$$(SDCC) $$(CFLAGS) $(COPTFLAGS) -c $$< -o $$@
			```
		
	1.3 Assemble ASM sources (and delete built-$(1) file)
			```
			$$($(1)_ASM_RELS): %.rel: %.s
				$$(RM) built-$(1)
				$$(SDAS) $$(ASMFLAGS) -o $$@ $$<
			```

	1.4 Copy Pre-compiled Objects (and delete built-$(1) file)
			```
			$$($(1)_COPIED_RELS): %.rel: %.rel_ %.lst_
				$$(RM) built-$(1)
				$$(CP) $$*.rel_ $$*.rel
				$$(CP) $$*.lst_ $$*.lst
			```

	2 Define All Object Files
		```
		$(1)_ALL_RELS := $$( $(1)_COMPILED_RELS) $$($(1)_ASM_RELS) $$($(1)_COPIED_RELS )
		```

	3 ISR Detection (Perl)
		```
		$(1)_ISR_FOUND := $$(shell perl -ne 'if (/\b_?nmi_handler\b/) { print $$$$ARGV; exit }' $$($(1)_CSRCS) $$($(1)_RELSRCS) /dev/null)
		```

	4 HANDLER_OBJ Logic
		```
		ifneq ($$($(1)_ISR_FOUND),)
			# Case A: User provided an ISR
			$(1)_HANDLER_OBJ := $$(addsuffix .rel, $$(basename $$($(1)_ISR_FOUND)))
		else
			$(1)_HANDLER_OBJ := _defaults/nmi_handler.rel
		endif
		```

	5 NON_HANDLER_OBJ Logic
		```
		$(1)_NON_HANDLER_OBJ := $$(filter-out $$($(1)_HANDLER_OBJ), $$($(1)_ALL_RELS))
		```

	6 STARTUP_OBJ Logic
		```
		ifneq ($(wildcard $(1)/startup.s),)
			$(1)_STARTUP_OBJ := $(1)/startup.rel
		else
			# Else -> use _defaults/startup.rel/.lst
			$(1)_STARTUP_OBJ := _defaults/startup.rel
		endif
		```

	7 MEMMAP Logic
		```
		ifneq ($(wildcard $(1)/memmap.ld),)
			$(1)_MEMMAP := $(1)/memmap.ld
		else
			$(1)_MEMMAP := _defaults/memmap.ld
		endif
		```
	8 Linker Rule
		```
		$(1)/$(1).ihx: $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) $$($(1)_MEMMAP)
			@echo "NON_HANDLER_OBJ: $$($(1)_NON_HANDLER_OBJ)"
			@echo "HANDLER_OBJ:     $$($(1)_HANDLER_OBJ)"
			@echo "STARTUP_OBJ:     $$($(1)_STARTUP_OBJ)"
			@echo "MEMMAP:          $$($(1)_MEMMAP)"
			@echo ""
			@$(GREP) "^\s*-[A-Za-z]" $$($(1)_MEMMAP)
			@echo ""
			$(SDCC) $(LDFLAGS) $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) -Wl-u -Wl-f,$$($(1)_MEMMAP) -o $$@
		```
	9. Binary/Disassembly Rule
		```
		$(1)/$(1).bin: $(1)/$(1).ihx
			@echo "...Generating Binary and Disassembly $(1).bin and $(1).txs..."
			$(SDOBJCOPY) -I ihex -O binary $$< $$@
			@echo "$(Z80DASM) $(DASMFLAGS) $$@ 2> /dev/null"
			@$(Z80DASM) $(DASMFLAGS) $$@ 2> /dev/null | \
			awk ' \
			BEGIN { count = 0; } \
			/^[ \t]+nop[ \t]+;[0-9a-fA-F]{4}[ \t]+00.*$$$$/ { \
				buffer[count++] = $$$$0; \
				next; \
			} \
			{ \
				if (count > 3) { \
					print buffer[0]; \
					print "    ..."; \
					print buffer[count-1]; \
				} \
				else { for (i=0; i<count; i++) print buffer[i]; } \
				count = 0; \
				print $$$$0; \
			} \
			END { \
				if (count > 3) { \
					print buffer[0]; \
					print "    ..."; \
					print buffer[count-1]; \
				} \
				else { for (i=0; i<count; i++) print buffer[i]; } \
			}' > $$(@:%.bin=%.txs)
			@$(CP) $$@ ../sim/
			touch built-$(1)
			@echo "----------------------------------------------------------------"
			@echo ""
		```

**End For each `codefolder`:**

-"clean" by doing:
	```
	$(RM) ../sim/*.bin
	```
	and going into `_defaults` folder and do:
	```
	$(RM) *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs
	``` 
	and for every `codefolder`, do:
	```
	$(RM) built-codefolder
	$(RM) *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs
	```


