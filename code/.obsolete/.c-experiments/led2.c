#include <stdint.h>
#include <stdbool.h>

void im1_handler(void) __interrupt;
void nmi_handler(void);

// TEACHING POINT 1: Cast the number to a pointer immediately.
// "Treat the number 0x4000 as an address of a volatile unsigned byte."
#define LED_PTR  ((volatile uint8_t *) 0x4000U)
#define COUNTER  ((volatile uint8_t *) 0x8000U)

void delay(uint8_t d) {
  // TEACHING POINT 2: Because we used a macro, this works everywhere.
  // We don't need to pass a variable; we just write to the address.
  *COUNTER = 0;
  while (*COUNTER < d) {
    *COUNTER = *COUNTER + 1;
  }
}

void main(void) {
  // TEACHING POINT 3: No setup required. 
  // We just write to the hardware directly.
  
  while (true) {
    *LED_PTR = 1;  // Turn LED ON
    delay(2);
    *LED_PTR = 0;  // Turn LED OFF
    delay(2);
  }
}

void im1_handler(void) __interrupt {}
void nmi_handler(void) {}