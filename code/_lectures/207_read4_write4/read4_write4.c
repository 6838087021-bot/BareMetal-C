// 05-207 (NEW!!!)
#include <stdbool.h>
#include <stdint.h>

#define LED0    ((volatile bool *)0xE000U)
#define TOGGLE0 ((volatile bool *)0xC000U)

void main(void) {
    volatile bool *led    = LED0;
    volatile bool *toggle = TOGGLE0;

    while (true) {

        uint8_t i = 0;
        while (i < 4) {
            if (*(toggle + i)) {
                *(led + i) = false;
            } else {
                *(led + i) = true;
            }
            i = i + 1;
        }
    }
}
