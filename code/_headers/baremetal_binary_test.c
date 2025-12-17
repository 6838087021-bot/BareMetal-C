#include <stdint.h>
#include "baremetal_binary.h"

// Point to the "Magic I/O" area defined in your memory map (0xC000 - 0xFFFF)
// 'volatile' is critical: it prevents the compiler from deleting "useless" writes.
volatile uint8_t * const MAGIC_IO = (volatile uint8_t *)0xC000;

void main(void) {
    // 1. Standard Pattern (0xAA / 170)
    // Goal: Verify basic interleaving works
    *MAGIC_IO = B8(10101010); // Should be 0xAA

    // 2. All Zeros with leading zeros logic (0x05)
    // Goal: Verify the 0x##d paste works with leading zeros
    *MAGIC_IO = B8(00000101); // Should be 0x05

    // 3. High Nibble Only (0xF0 / 240)
    // Goal: Verify upper bits shifting
    *MAGIC_IO = B8(11110000); // Should be 0xF0

    // 4. Combined logic (OR-ing two macros)
    // Goal: Verify the compiler folds even this complex expression into one constant
    *MAGIC_IO = B8(11000000) | B8(00000011); // Should be 0xC3
}
