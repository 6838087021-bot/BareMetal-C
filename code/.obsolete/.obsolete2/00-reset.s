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

; Jump to the C code entry point.

.globl _main      ; Linker resolves to C main function (note underscore)

  JP _main

; -----------------------------------------------------------------
; Interrupt Mode 1 Vector
; We set IM 1, so all maskable interrupts jump here (0x0038).
; -----------------------------------------------------------------
.area _IM1_VECTOR (ABS)
.org 0x0038

  HALT      ; Stop the CPU.

; -----------------------------------------------------------------
; Non-Maskable Interrupt (NMI) Vector
; -----------------------------------------------------------------
.area _NMI_VECTOR (ABS)
.org 0x0066

.globl _nmi_isr   ; Linker resolves to C nmi_isr function

  JP _nmi_isr