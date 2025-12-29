// 05-207 (NEW!!!)
#include <stdbool.h>
#include <stdint.h>

#define LED0    ((volatile bool *)0xE000U)
#define TOGGLE0 ((volatile bool *)0xC000U)

void main(void) {
    volatile bool *led    = LED0;
    volatile bool *toggle = TOGGLE0;

    while (true) {

        for (uint8_t i = 0; i < 4; i = i + 1) {
            if (*(toggle + i)) {
                *(led + i) = false;
            } else {
                *(led + i) = true;
            }
        }
    }
}
