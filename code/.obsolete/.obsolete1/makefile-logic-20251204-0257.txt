See the attached makefile and check the logic that it follows this pseudo-code.
point out any discrepancy.

definitions: NNN = Unique 3-digit prefixes extracted from existing files matching [0-9]{3}-*.c, *.s, or *.rel_

-Do not read comments
-Do not modify comments

-defines:
SDAS      := sdasz80
SDCC      := sdcc
SDOBJCOPY := sdobjcopy
Z80DASM   := z80dasm

ASMFLAGS  := -l
CFLAGS    := -mz80 --std c99 --Werror
LDFLAGS   := -mz80 --no-std-crt0
DASMFLAGS := -a -l -t -g0

RM := rm -f
CP := cp

-always do:
	default-%.rel default-%.lst: default-%.s
		$(SDAS) $(ASMFLAGS) -o $@ $<
	
	default-%.rel default-%.lst: default-%.c
		$(SDCC) $(CFLAGS) -c $< -o $@

-Target "all" depends only on NNNs found in the scan above.

For each found NNN,

  $(1)_CSRCS   := $(wildcard $(1)-*.c)
	$(1)_ASRCS   := $(wildcard $(1)-*.s)
	$(1)_RELSRCS := $(wildcard $(1)-*.rel_)
	
	# 1.2 Compile C sources
	$$($(1)_COMPILED_RELS): %.rel: %.c
		$$(SDCC) $$(CFLAGS) -c $$< -o $$@
	
	# 1.3 Assemble ASM sources
	$$($(1)_ASM_RELS): %.rel: %.s
		$$(SDAS) $$(ASMFLAGS) -o $$@ $$<
	
	# 1.4 Copy Pre-compiled Objects
	$$($(1)_COPIED_RELS): %.rel: %.rel_ %.lst_
		$$(CP) $$*.rel_ $$*.rel
		$$(CP) $$*.lst_ $$*.lst

	$(1)_ALL_RELS := $$($(1)_COMPILED_RELS) $$($(1)_ASM_RELS) $$($(1)_COPIED_RELS)

  $(1)_ISR_FOUND := $$(shell perl -ne 'if (/\b_?nmi_handler\b/) { print $$$$ARGV; exit }' $$($(1)_CSRCS) $$($(1)_RELSRCS) /dev/null)

  if $ISR_FOUND is not BLANK:
    $HANDLER_OBJ is (addsuffix .rel, (basename $_ISR_FOUND))
  else
    copy default-nmi_handler.lst to NNN-nmi_handler.lst
    copy default-nmi_handler.rel to NNN-nmi_handler.rel
    $HANDLER_OBJ is NNN-nmi_handler.rel
  endif

  $NON_HANDLER_OBJ = NNN-*.rel with $HANDLER_OBJ filtered out

  # comment: must do grep before checking for existence of NNN-startup.s

  If NNN-startup.s exists,
    set $STARTUP_OBJ to NNN-startup.rel
  else
    copy default-startup.lst to NNN-startup.lst
    copy default-startup.rel to NNN-startup.rel
    set $STARTUP_OBJ to NNN-startup.rel
  endif
    
  if NNN-memmap.ld exists:
    $MEMMAP is NNN-memmap.ld
  else
    $MEMMAP is default-memmap.ld
  endif
  
	pretty echo of the following: $_NON_HANDLER_OBJ, $_HANDLER_OBJ, $_STARTUP_OBJ, $_MEMMAP
     
  generate NNN-run.ihx by:
    $$(SDCC) $$(LDFLAGS) $STARTUP_OBJ $HANDLER_OBJ $NON_HANDLER_OBJ -Wl-u -Wl-f,$MEMMAP -o $$@
    
  -convert NNN-run.ihx to NNN-run.bin by:
    $(1)-run.bin: $(1)-run.ihx
    	$(SDOBJCOPY) -I ihex -O binary $< $@
      @echo "$(Z80DASM) $(DASMFLAGS) $$@ 2> /dev/null"
    	$(Z80DASM) $(DASMFLAGS) $@ 2> /dev/null | \
        awk ' \
        BEGIN { count = 0; } \
        /^[ \t]+nop[ \t]+;[0-9a-fA-F]{4}[ \t]+00.*$$/ { \
            buffer[count++] = $$0; \
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
            print $$0; \
        } \
        END { \
            if (count > 3) { \
                print buffer[0]; \
                print "    ..."; \
                print buffer[count-1]; \
            } \
            else { for (i=0; i<count; i++) print buffer[i]; } \
    	}' > $(@:%.bin=%.txs)
		
    -copy NNN-run.bin to ../sim

EndFor each NNN

-"clean" by $(RM) *.asm *.bin ../sim/*.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs
