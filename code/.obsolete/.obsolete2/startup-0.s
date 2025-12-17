; startup-0.s
; This is the reset vector at 0x0000.

.area _RESET_VECTOR (ABS)  ; Define an absolute (non-relocatable) segment
.org 0x0000

; Set SP to 0x0100.
LD SP, #0x0100

; Jump to the hard-coded C code address.
JP 0x0090