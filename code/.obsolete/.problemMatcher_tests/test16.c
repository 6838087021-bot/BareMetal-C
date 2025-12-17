/* test-qualifier.c */
#include <string.h>
void main(void) {
    volatile char *hw_register = (char*)0x8000;
    // Warning: passing 'volatile char *' to parameter of type 'const char *'
    size_t len = strlen(hw_register); 
}
