/* test-asm.c */
void main(void) {
    __asm
        ld a, #0x10000
    __endasm;
}
