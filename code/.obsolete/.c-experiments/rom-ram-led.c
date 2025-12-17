#include <stdint.h>
#include <stdbool.h>

// Define the pointers as macros directly, avoiding Global Variables.
#define LED_ADDR ((volatile uint8_t *)0x4000U)
#define COUNTER  ((volatile uint8_t *)0x8000U)

void delay(uint8_t d) {
  *COUNTER = 0;
  while (*COUNTER < d) {
	*COUNTER = *COUNTER + 1;
  }
}

void main(void) {
  while (true) {
	*LED_ADDR = 1;
    delay(2);
	*LED_ADDR = 0;
	delay(2);
  }
}
