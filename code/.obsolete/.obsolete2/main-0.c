
#include <stdint.h>

#define ADDR0 0x0060U
#define ADDR1 0x0062U

//volatile unsigned char dummy_var;
volatile uint8_t dummy_var1;
volatile uint8_t dummy_var2 = 20;

void main(void)
{
  uint8_t *count0 = (volatile uint8_t *) ADDR0;
  uint8_t *count1 = (volatile uint8_t *) ADDR1;
//  unsigned char *count0 = (volatile unsigned char *) ADDR0;
//  unsigned char *count1 = (volatile unsigned char *) ADDR1;  
  
  *count0 = 0;
  *count1 = 0;

  while (1) {
    for (uint8_t i = 0; i < 3; i = i + 1) {
//    for (unsigned char i = 0; i < 3; i = i + 1) {
      *count1 = *count1 + 1;
    }
    *count0 = *count0 + 1;  
  }
}
