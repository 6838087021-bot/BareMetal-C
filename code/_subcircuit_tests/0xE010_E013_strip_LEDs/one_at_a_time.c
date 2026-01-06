// 06-2
#include <stdbool.h>
#include <stdint.h>
#include "baremetal_binary.h"

#define STRIP_WRITE_ONLY ((volatile uint8_t *)0xE010U)
#define SHADOW ((uint8_t *)0x4010U)
#define COUNTER ((volatile uint16_t *)0x4000U)

void delay(uint16_t n) {
    volatile uint16_t *c = COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}

void main(void){

    *(STRIP_WRITE_ONLY + 0) = *(SHADOW + 0) = B8(01010101);
    *(STRIP_WRITE_ONLY + 1) = *(SHADOW + 1) = B8(00110011);
    *(STRIP_WRITE_ONLY + 2) = *(SHADOW + 2) = B8(00001111);
    *(STRIP_WRITE_ONLY + 3) = *(SHADOW + 3) = B8(01101001);

    while (true) {

        for (int8_t i = 3; i >= 0; i = i - 1) {
            *(STRIP_WRITE_ONLY + i) = *(SHADOW + i);
            delay(2000);
            *(STRIP_WRITE_ONLY + i) = 0;
        }
    }
}
