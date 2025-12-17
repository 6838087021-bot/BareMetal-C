#include <stdint.h>
#include <stdbool.h>

#define LED_BASE ((volatile uint8_t * const) 0xE000U)
#define TOGGLE_BASE ((volatile const uint8_t * const) 0xC000U)

void main(void) {

	volatile const uint8_t * const read_ptr = TOGGLE_BASE;
	volatile uint8_t * const write_ptr = LED_BASE;

	// run around, copy TOGGLEs to LED
	while (true) {
		for (uint8_t c = 0; c < 4; c = c+1) {
			*(write_ptr   ) = *(read_ptr   );
			*(write_ptr +1) = *(read_ptr +1);
			*(write_ptr +2) = *(read_ptr +2);
			*(write_ptr +3) = *(read_ptr +3);
		}
	}
}