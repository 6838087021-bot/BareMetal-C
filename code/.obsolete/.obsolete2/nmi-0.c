// nmi_isr.c - This file contains our NMI handler.

// pragma tells SDCC to put code in this file into a new segment named "NMI_SEG".
#pragma codeseg NMI_SEG

// includes C99 standard integer types
#include <stdint.h>

// memory location of our counter

#define NMI_COUNT 0x0064U

// The NMI service routine.
// __critical = ends with RETN (for NMI)
// __interrupt = is an ISR (saves/restores registers)

void nmi_isr(void) __critical __interrupt
{
uint8_t *count = (volatile uint8_t *) NMI_COUNT;
uint8_t v = *count;
//  unsigned char *count = (volatile unsigned char *) NMI_COUNT;
//  unsigned char v = *count;
  
  *count = *count + 1;
}
