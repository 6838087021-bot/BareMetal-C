#ifndef BAREMETAL_BINARY_H
#define BAREMETAL_BINARY_H

#include <stdint.h>

/*
* B8(d) - Binary Literal Helper for C99
* * Usage:
* uint8_t val = B8(10101010);
* uint8_t low = B8(00000101);
*
* How it works:
* The macro uses the token pasting operator (##) to prefix '0x' to the
* argument. It then treats the input as Hexadecimal digits, where each
* digit corresponds to a single bit in the final output.
* * Constraints:
* - Input must be 8 digits or fewer.
* - Only use 0s and 1s.
* - Do not pass variables, only literal numbers.
*/

#define B8(d) ((uint8_t) ( \
((0x##d & 0x00000001UL) ? 0x01 : 0) | \
((0x##d & 0x00000010UL) ? 0x02 : 0) | \
((0x##d & 0x00000100UL) ? 0x04 : 0) | \
((0x##d & 0x00001000UL) ? 0x08 : 0) | \
((0x##d & 0x00010000UL) ? 0x10 : 0) | \
((0x##d & 0x00100000UL) ? 0x20 : 0) | \
((0x##d & 0x01000000UL) ? 0x40 : 0) | \
((0x##d & 0x10000000UL) ? 0x80 : 0) ))

#endif // BAREMETAL_BINARY_H
