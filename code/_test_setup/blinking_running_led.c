#include <stdbool.h>
#include <stdint.h>

#define LED0 ((volatile bool *)0xE000U)

#define COUNTER ((volatile uint16_t *)0x40F0U)

void delay(uint16_t n) {
    uint16_t *c = COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}

void main(void) {

    volatile bool *led;

    uint16_t on  = 1500;
    uint16_t off = 1000;

    while (true) {
        for (uint8_t i = 0; i < 4; i = i + 1) {
            led = LED0 + i;
            *led = true;
            delay(on);
            *led = false;
            delay(off);
            *led = true;
            delay(on);
            *led = false;
        }
    }
}
