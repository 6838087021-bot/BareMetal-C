; rom-ram-led.s 

    .module crt0
    .globl  _main

    ; -----------------------------------------------------------
    ; 1. Reset Vector (0x0000)
    ; -----------------------------------------------------------
    .area   _HEADER (ABS)
    .org    0x0000

__reset:
    jp      start

    ; -----------------------------------------------------------
    ; 2. Startup Code (ROM)
    ; -----------------------------------------------------------
    .area   _CODE

start:
    ; A. Initialize Stack Pointer (Top of 64K RAM)
    ld      sp, #0xFFFF

    ; B. Initialize Global Variables
    ;    This is the critical step for your pointers!
    call    gsinit

    ; C. Run C code
    call    _main

hang:
    jr      hang

    ; -----------------------------------------------------------
    ; 3. Global Initialization Section
    ;    SDCC generates the code to set *led_addr = 0x4000 here.
    ; -----------------------------------------------------------
    
    .area   _GSINIT
gsinit:
    ; (Linker inserts instructions here automatically)

    .area   _GSINIT_TAIL
    ret