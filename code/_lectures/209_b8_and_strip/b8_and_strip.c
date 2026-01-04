// 06-209
#include <stdlib.h>
#include <stdbool.h>
#include "baremetal_binary.h" // for B8()
#include "baremetal_delay.h"  // for baremetal_delay()

#define LED_STRIP ((volatile uint8_t *)0xE010U)

void main(void) {
    volatile uint8_t *s = LED_STRIP;

    while (true) {
        *s = B8(10101111);     // X.X.XXXX
        baremetal_delay(4000);
        *s = B8(11110101);     // XXXX.X.X
        baremetal_delay(4000);
        *s = B8(01010101);     // .X.X.X.X
        baremetal_delay(4000);
    }
}
