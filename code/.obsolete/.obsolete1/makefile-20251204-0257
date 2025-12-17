# -----------------------------------------------------------------------------
# Tools
# -----------------------------------------------------------------------------
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

# -----------------------------------------------------------------------------
# Definitions: NNN = 3-digit number, from 000-999
# Scan for [0-9]{3}-*.c, [0-9]{3}-*.s OR [0-9]{3}-*.rel_
# -----------------------------------------------------------------------------
SOURCES  := $(wildcard [0-9][0-9][0-9]-*.c) $(wildcard [0-9][0-9][0-9]-*.s) $(wildcard [0-9][0-9][0-9]-*.rel_)
PREFIXES := $(sort $(foreach s,$(SOURCES),$(firstword $(subst -, ,$(s)))))

# -----------------------------------------------------------------------------
# Target: "all" - Iterate through all NNN's
# -----------------------------------------------------------------------------
all: $(PREFIXES:%=%-run.bin)

# -----------------------------------------------------------------------------
# "Always Do" Rules
# -----------------------------------------------------------------------------
default-%.rel default-%.lst: default-%.s
	$(SDAS) $(ASMFLAGS) -o $@ $<

default-%.rel default-%.lst: default-%.c
	$(SDCC) $(CFLAGS) -c $< -o $@

# -----------------------------------------------------------------------------
# Logic Per NNN Prefix
# -----------------------------------------------------------------------------
define DEFINE_RUN_RULES

# 1. Sources Check --bomb if NNN-*.c, NNN-*.s, or NNN-*.rel_ doesn't exist
$(1)_CSRCS   := $(wildcard $(1)-*.c)
$(1)_ASRCS   := $(wildcard $(1)-*.s)
$(1)_RELSRCS := $(wildcard $(1)-*.rel_)

# 1.1 Convert source lists to object lists
$(1)_COMPILED_RELS := $$(patsubst %.c, %.rel, $$($(1)_CSRCS))
$(1)_ASM_RELS      := $$(patsubst %.s, %.rel, $$($(1)_ASRCS))
$(1)_COPIED_RELS   := $$(patsubst %.rel_, %.rel, $$($(1)_RELSRCS))

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

# 2. Define All Object Files
$(1)_ALL_RELS := $$($(1)_COMPILED_RELS) $$($(1)_ASM_RELS) $$($(1)_COPIED_RELS)

# 3. ISR Detection (Perl)
$(1)_ISR_FOUND := $$(shell perl -ne 'if (/\b_?nmi_handler\b/) { print $$$$ARGV; exit }' $$($(1)_CSRCS) $$($(1)_RELSRCS) /dev/null)

# 4. HANDLER_OBJ Logic
ifneq ($$($(1)_ISR_FOUND),)
    # Case A: User provided an ISR
    $(1)_HANDLER_OBJ := $$(addsuffix .rel, $$(basename $$($(1)_ISR_FOUND)))
else
    # Case B: Use Default ISR (Note: Use TABS below for the recipe lines!)
    $(1)-nmi_handler.rel: default-nmi_handler.rel default-nmi_handler.lst
		$$(CP) default-nmi_handler.rel $$@
		$$(CP) default-nmi_handler.lst $$(@:.rel=.lst)
    $(1)_HANDLER_OBJ := $(1)-nmi_handler.rel
endif

# 5. NON_HANDLER_OBJ Logic
$(1)_NON_HANDLER_OBJ := $$(filter-out $$($(1)_HANDLER_OBJ), $$($(1)_ALL_RELS))

# 6. STARTUP_OBJ Logic
ifneq ($(wildcard $(1)-startup.s),)
    $(1)_STARTUP_OBJ := $(1)-startup.rel
else
    # Else -> copy default-startup.rel/.lst to NNN-startup.rel/.lst
    $(1)-startup.rel: default-startup.rel default-startup.lst
		$$(CP) default-startup.rel $$@
		$$(CP) default-startup.lst $$(@:.rel=.lst)
    $(1)_STARTUP_OBJ := $(1)-startup.rel
endif

# 7. MEMMAP Logic
ifneq ($(wildcard $(1)-memmap.ld),)
    $(1)_MEMMAP := $(1)-memmap.ld
else
    $(1)_MEMMAP := default-memmap.ld
endif

# 8. Linker Rule
$(1)-run.ihx: $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) $$($(1)_MEMMAP)
	@echo "[$(1)] "
	@echo "[$(1)] NON_HANDLER_OBJ: $$($(1)_NON_HANDLER_OBJ)"
	@echo "[$(1)] HANDLER_OBJ:     $$($(1)_HANDLER_OBJ)"
	@echo "[$(1)] STARTUP_OBJ:     $$($(1)_STARTUP_OBJ)"
	@echo "[$(1)] MEMMAP:          $$($(1)_MEMMAP)"
	$(SDCC) $(LDFLAGS) $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) -Wl-u -Wl-f,$$($(1)_MEMMAP) -o $$@

# 9. Binary/Disassembly Rule
$(1)-run.bin: $(1)-run.ihx
	@echo "...Generating Binary and Disassembly $(1)-run.bin and $(1)-run.txs..."
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
	$(CP) $$@ ../sim/
	@echo "----------------------------------------------------------------"
	@echo ""
endef

# Iterate over all detected NNN and evaluate the rules
$(foreach P,$(PREFIXES),$(eval $(call DEFINE_RUN_RULES,$(P))))

# -----------------------------------------------------------------------------
# Clean
# -----------------------------------------------------------------------------
clean:
	$(RM) *.asm *.bin ../sim/*.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs