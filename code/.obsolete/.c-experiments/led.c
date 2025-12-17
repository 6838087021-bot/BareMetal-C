#include <stdint.h>
#include <stdbool.h>

#define LED_ADDR 0x4000U
#define COUNTER  0x8000U

// Define pointers, but do NOT initialize them here
volatile uint8_t *led_addr;
volatile uint8_t *counter;

void delay(uint8_t d) {
  *counter = 0;
  while (*counter < d) {
    *counter = *counter + 1;
  }
}

void main(void) {
  // Initialize them explicitly in code!
  // This generates actual CPU instructions to write 0x4000 to the variable.
  led_addr = (volatile uint8_t *) LED_ADDR;
  counter  = (volatile uint8_t *) COUNTER;

  while (true) {
    *led_addr = 1;
    delay(2);
    *led_addr = 0;
    delay(2);
  }
}