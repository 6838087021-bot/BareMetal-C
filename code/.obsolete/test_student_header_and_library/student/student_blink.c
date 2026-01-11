#include <stdbool.h>
#include <stdint.h>
#include "sdelay.h"

#define LED0 ((volatile bool *)0xE000U)

void main(void) {

    volatile bool *led;

    uint16_t on  = 800;
    uint16_t off = 600;

    while (true) {
        for (uint8_t i = 0; i < 4; i = i + 1) {
            led = LED0 + i;
            *led = true;
            sdelay(on);
            *led = false;
            sdelay(off);
            *led = true;
            sdelay(on);
            *led = false;
        }
    }
}
