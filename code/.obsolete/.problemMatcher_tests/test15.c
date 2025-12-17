/* test-overflow.c */
// Allocating 50KB array in a 64KB Z80 space (might clash with code/stack)
unsigned char huge_data[65530]; 

void main(void) {
    huge_data[0] = 1;
}
