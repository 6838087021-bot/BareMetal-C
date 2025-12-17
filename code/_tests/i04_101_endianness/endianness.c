#include <stdbool.h>
#include <stdint.h>

#define ADDRESS 0x4008U

void main(void) {

    volatile uint32_t * store = (volatile uint32_t *) ADDRESS;
    
    *store = 0x1A2B3C4D;
    
    while (true) {
    }
}
