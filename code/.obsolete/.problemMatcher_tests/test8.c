/* test-asm.c */
void main(void) {
    __asm
        invalid_opcode
    __endasm;
}
