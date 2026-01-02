// 05-207 (NEW!!!)
#include <stdbool.h>
#include <stdint.h>

#define A0 ((volatile uint8_t *)0x4000U) // for loop
#define B0 ((volatile uint8_t *)0x4010U) // "fixed" while loop
#define C0 ((volatile uint8_t *)0x4020U) // broken while loop

#define LED0 ((volatile bool *)0xE000) // light to turn on if all runs are ok

void main(void) {
    volatile uint8_t *a = A0;
    volatile uint8_t *b = B0;
    volatile uint8_t *c = C0;

    volatile bool *led = LED0;

    uint8_t i;  // common loop counter

    // make sure light is off
    *led = false;

    // for should be ok
    for (i = 0; i < 10; i = i + 1) {
        if (i == 6) {
            continue;
        }
        *(a + i) = i;
    }
    // "fixed" while should be ok, but not DRY
    i = 0;
    while (i < 10) {
        if (i == 6) {
            i = i + 1;
            continue;
        }
        *(b + i) = i;
        i = i + 1;
    }
    // broken while loop, stuck at i = 6
    i = 0;
    while (i < 10) {
        if (i == 6) {
            continue;
        }
        *(c + i) = i;
        i = i + 1;
    }
    // turn on light
    *led = true;

    while (true) {
    }

}
