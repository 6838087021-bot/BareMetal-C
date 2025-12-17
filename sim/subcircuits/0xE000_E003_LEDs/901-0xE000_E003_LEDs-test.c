#include <stdint.h>
#include <stdbool.h>

#define LED_BASE ((volatile uint8_t * const) 0xE000U)

void main(void) {

	volatile uint8_t * const p = LED_BASE;

	// turn it all off
	for (uint8_t c = 0; c < 4; c = c+1) {
		*(p + c) = false;
	}

	// run around
	while (true) {
		for (uint8_t c = 0; c < 6; c = c+1) {
			if (c == 0) {
				*(p+1) = false;
				*(p)   = true;
			}
			else if (c == 1) {
				*(p)   = false;
				*(p+1) = true;
			}
			else if (c == 2) {
				*(p+1) = false;
				*(p+2) = true;
			}
			else if (c == 3) {
				*(p+2) = false;
				*(p+3) = true;
			}
			else if (c == 4) {
				*(p+3) = false;
				*(p+2) = true;
			} else {
				*(p+2) = false;
				*(p+1) = true;
			}	
		}
	}
}