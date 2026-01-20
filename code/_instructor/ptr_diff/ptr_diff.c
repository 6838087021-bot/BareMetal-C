#include <stdint.h>
#include <stddef.h> // get ptrdiff_t

#define SIZEOF_PTRDIFF_T ((int32_t *)0x4000U)
#define SIZEOF_SIZE_T ((uint16_t *)0x4004U)
#define POSITIVE_PTRDIFF_T ((ptrdiff_t *)0x4008U)
#define NEGATIVE_PTRDIFF_T ((ptrdiff_t *)0x400CU)
#define PTRDIFF_UINT8 ((ptrdiff_t *)0x4010U)
#define PTRDIFF_UINT16 ((ptrdiff_t *)0x4014U)

void main(void){
    *SIZEOF_PTRDIFF_T = sizeof (ptrdiff_t);
    *SIZEOF_SIZE_T = sizeof( size_t);
    uint8_t *p1 = (uint8_t *) 0x0100U;
    uint8_t *p2 = (uint8_t *) 0xC100U;
    *POSITIVE_PTRDIFF_T = p2 - p1;
    *NEGATIVE_PTRDIFF_T = p1 - p2;

    *PTRDIFF_UINT8  = ((uint8_t *)0xC200U) - ((uint8_t *)0x0100U);
    *PTRDIFF_UINT16 = ((uint16_t *)0xD300U) - ((uint16_t *)0x0200U);
}
