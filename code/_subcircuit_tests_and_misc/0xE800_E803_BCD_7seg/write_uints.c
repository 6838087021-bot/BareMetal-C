#include <stdint.h>
#include <stdbool.h>
#include "baremetal_delay.h"

#define UINT32 ((volatile uint32_t *)0xE800U)
#define UINT16 ((volatile uint16_t *)0xE800U)
#define UINT8  ((volatile uint8_t  *)0xE800U)
#define DELAY (3000)

void main(void){
    while (true) {
        *UINT32 = 0x12345678U;
        baremetal_delay(DELAY);
        *(UINT16)     = 0x2345U;
        *(UINT16 + 1) = 0x6789U;
        baremetal_delay(DELAY);
        *(UINT8)     = 0x34U;
        *(UINT8 + 1) = 0x56U;
        *(UINT8 + 2) = 0x78U;
        *(UINT8 + 3) = 0x9AU;
        baremetal_delay(DELAY);
    }
}
