# Tools
SDAS      := sdasz80
SDCC      := sdcc
SDOBJCOPY := sdobjcopy

CFLAGS    := -mz80 --std c99 --Werror
LDFLAGS   := -mz80 --no-std-crt0

# cross-platform clean
ifeq ($(COMSPEC)$(ComSpec),)        # empty on Unix
  RM := rm -f
else
  RM := del /F /Q                   # Windows
endif

# Detect "uniquename" projects by finding all *.ld files
# e.g., if you have foo.ld, PROJECT will contain 'foo'
PROJECTS := $(patsubst %.ld,%,$(wildcard *.ld))

# Default: build a .bin for every detected project
all: $(PROJECTS:%=%.bin)

# Generic Assembly: uniquename.s -> uniquename.rel
%.rel: %.s
	$(SDAS) -o $@ $<

# Generic C compile: any *.c -> *.rel
# (Kept in case you mix C and Assembly)
%.rel: %.c
	$(SDCC) $(CFLAGS) -c $<

# Template to define the link rule for each project
define DEFINE_PROJECT_RULES

# Link uniquename.rel (from uniquename.s) using uniquename.ld
# We also look for any matching C files (uniquename-*.c) just in case,
# but strictly linking uniquename.rel and uniquename.ld is the priority.
$(1).ihx: $(1).rel $(1).ld
	$$(SDCC) $$(LDFLAGS) $(1).rel -Wl-f,$(1).ld -o $$@

endef

# Instantiate rules for every detected project
$(foreach P,$(PROJECTS),$(eval $(call DEFINE_PROJECT_RULES,$(P))))

# Convert IHX -> BIN
%.bin: %.ihx
	$(SDOBJCOPY) -I ihex -O binary $< $@

clean:
	$(RM) *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym