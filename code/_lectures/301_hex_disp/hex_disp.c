#include <stdint.h>
#include <stdbool.h>

#define HEX_DISP ((volatile uint16_t *)0xE800U)

void main(void){
    *HEX_DISP = 0xBEAD;
    while (true) {
    }
}
