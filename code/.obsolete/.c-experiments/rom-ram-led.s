; This is the reset vector at 0x0000.
; It initializes the bare minimum required to jump
; to the SDCC-compiled C 'main' function.

.area _RESET_VECTOR (ABS)  ; Define an absolute (non-relocatable) segment
.org 0x0000

  DI        ; Disable interrupts IMMEDIATELY.
  IM 1      ; Set a known, safe interrupt mode (jumps to 0x0038)

; These values will be provided by the linker

; Set SP
.globl STACK_TOP

  LD SP, #STACK_TOP

    ; B. Initialize Global Variables
    ;    This is the critical step for your pointers!
    call    gsinit

; Jump to the C code entry point.

.globl _main      ; Linker resolves to C main function (note underscore)

  call _main

hang:
    jr      hang

; -----------------------------------------------------------------
; Interrupt Mode 1 Vector
; We set IM 1, so all maskable interrupts jump here (0x0038).
; -----------------------------------------------------------------
.area _IM1_VECTOR (ABS)
.org 0x0038

trap_loop:
    JR trap_loop    ; Jump back to the label

; -----------------------------------------------------------------
; Non-Maskable Interrupt (NMI) Vector
; -----------------------------------------------------------------
;.area _NMI_VECTOR (ABS)
;.org 0x0066

;.globl _nmi_isr   ; Linker resolves to C nmi_isr function

;  JP _nmi_isr

    ; -----------------------------------------------------------
    ; 3. Global Initialization Section
    ;    SDCC generates the code to set *led_addr = 0x4000 here.
    ; -----------------------------------------------------------
    
    .area   _GSINIT
gsinit:
    ; (Linker inserts instructions here automatically)

    .area   _GSINIT_TAIL
    ret