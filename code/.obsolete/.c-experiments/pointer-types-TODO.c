#include <stdint.h>
#include <stdbool.h>

#define SIZEOF_BOOL   0x0070U
#define SIZEOF_UCHAR  0x0072U
#define SIZEOF_CHAR   0x0074U
#define SIZEOF_INT    0x0076U
#define SIZEOF_UINT   0x0078U
#define SIZEOF_PTR    0x007AU
#define SIZEOF_INT32  0x007CU
#define SIZEOF_UINT64 0x007EU

void main(void) {
  volatile uint8_t *sizeof_bool   = (volatile uint8_t *) SIZEOF_BOOL;
  volatile uint8_t *sizeof_uchar  = (volatile uint8_t *) SIZEOF_UCHAR;
  volatile uint8_t *sizeof_char   = (volatile uint8_t *) SIZEOF_CHAR;
  volatile uint8_t *sizeof_int    = (volatile uint8_t *) SIZEOF_INT;
  volatile uint8_t *sizeof_uint   = (volatile uint8_t *) SIZEOF_UINT;
  volatile uint8_t *sizeof_ptr    = (volatile uint8_t *) SIZEOF_PTR;
  volatile uint8_t *sizeof_int32  = (volatile uint8_t *) SIZEOF_INT32;
  volatile uint8_t *sizeof_uint64 = (volatile uint8_t *) SIZEOF_UINT64;

  *sizeof_bool   = sizeof (bool);
  *sizeof_uchar  = sizeof (unsigned char);
  *sizeof_char   = sizeof (char);
  *sizeof_int    = sizeof (int);
  *sizeof_uint   = sizeof (unsigned int);
  *sizeof_ptr    = sizeof (void *);
  *sizeof_int32  = sizeof (int32_t);
  *sizeof_uint64 = sizeof (uint64_t);

  while (true) {
  }
}