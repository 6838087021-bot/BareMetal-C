#include <stdint.h>
#include "instructor_addresses.h"
#include "sdelay.h"

void sdelay(uint16_t n) {
    volatile uint16_t * const c = DELAY_COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}
