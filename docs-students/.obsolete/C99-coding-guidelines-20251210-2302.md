# C99 Coding Guidelines for `Bare-Metal C` Course using `SDCC`

### **1. Macros & Preprocessor**

*Rationale: The preprocessor is a text substitution tool. Without strict syntax, operator precedence errors and side effects are inevitable.*

* **Rule 1.1: Use `U` Suffix for Data and Addresses.**
  * **When to use `U`:** Always append `U` to constants that represent **bit patterns**, **hex masks**, or **memory addresses**. This ensures they are treated as unsigned 16-bit values, preventing sign-extension bugs.
  * **When NOT to use `U`:** You do not need `U` for **scalar quantities**, such as shift counts (how *far* to shift) or loop counters (how *many* times to loop).
  * **Bad (Address interpreted as negative):** `#define START (0x8000)`
  * **Bad (Signed `1` shifted into sign bit):** `(1 << 15)`
  * **Good (Address):** `#define START (0x8000U)`
  * **Good (Mask Generator):** `(1U << 3)`  ← `1U` is the data being shifted.
  * **Good (Shift Count):** `pattern << 3` ← `3` is just a distance.
* **Rule 1.2: Parenthesize Macro Replacements.**
  * All macro values must be enclosed in parentheses to prevent operator precedence errors during expansion.
  * **Bad:** `#define OFFSET 0x10U + 0x02U`
  * **Bad (Violates strict rule):** `#define BASE_ADDR 0x8000U`
  * **Good:** `#define OFFSET (0x10U + 0x02U)`
  * **Good:** `#define BASE_ADDR (0x8000U)`
* **Rule 1.3: No Parameterized Macros.**
  * Do not use macros that take arguments (function-like macros). They are prone to side-effect bugs. Use `static inline` functions instead.
  * **Bad:** `#define ADDR_OFFSET(x) (BASE + x)`
  * **Good:** `static inline uint8_t* get_addr(uint8_t x) { return BASE + x; }`

---

### **2. Data Types & Precision**

*Rationale: On an 8-bit Z80, an int is 16-bit, but on modern CPUs, it is 32-bit. Ambiguity is the enemy of embedded systems.*

* **Rule 2.1: Always use `<stdint.h>` types.**
  * Never use `int`, `short`, or `long` for data storage.
  * Use `uint8_t` for data bus values (8-bit).
  * Use `uint16_t` for address bus values (16-bit).
* **Rule 2.2: Use bool from `<stdbool.h>` for logic.**
  * Use `true` and `false` for flags.
* **Rule 2.3: Avoid Floating Point.**
  * The Z80 has no FPU. Floats are emulated in software and are incredibly slow.

---

### **3. Memory Mapped I/O (MMIO)**

*Rationale: This is the core learning objective. Students must understand that "Writing to IO" is just "Writing to a specific memory address."*

* **Rule 3.1: The `volatile` keyword is mandatory for IO.**
  * Any pointer interacting with hardware *must* be declared `volatile`.
  * **Why:** Without `volatile`, the compiler may "optimize away" your reads/writes because it doesn't see the variable changing in code.
* **Rule 3.2: Typed Pointers for Hardware Addresses.**
  * Hardware addresses must be defined as cast pointers in a single macro. Do not define raw integer addresses separately.
  * **Format:** `#define NAME ((volatile type *) addressU)`
  * *Example:*
    ```C
    // Combined definition: Safe, Clean, Typed.
    #define LED_PORT     ((volatile uint8_t *) 0x4000U)

    // Usage: Explicit dereference required
    // 0xFFU used because it is a bit pattern (Rule 1.1)
    *LED_PORT = 0xFFU; 
    ```

---

### **4. Memory Management**

*Rationale: There is no OS to clean up messes. Memory is finite (SRAM).*

* **Rule 4.1: No Dynamic Memory Allocation.**
  * **Strictly forbidden:** `malloc()`, `calloc()`, `free()`.
* **Rule 4.2: Use `const` for Read-Only Data.**
  * Lookup tables (e.g., 7-segment display fonts) should be `const` to save RAM and prevent corruption.

---

### **5. Functions & Control Flow**

*Rationale: The Z80 stack is small and easy to overflow.*

* **Rule 5.1: No Recursion.**
  * Functions must not call themselves. Recursion leads to stack overflow.
* **Rule 5.2: Infinite Main Loop.**
  * Embedded programs never "exit". `main()` should end with `while(true)`.
* **Rule 5.3: Keep Functions Short.**
  * Limit functions to ~30 lines where possible.

---

### **6. Bit Manipulation**

*Rationale: Hardware control often requires changing 1 bit without affecting the other 7.*

* **Rule 6.1: Use Explicit Shifts and Masks.**
  * Do not use "Bit Fields". Use standard shifts with unsigned constants `(1U << 3)`.
* **Rule 6.2: Read-Modify-Write.**
  * To change one bit, read the port, modify the bit, write it back.
  * *Example: Set bit 3 HIGH (OR operation)*
    ```C
    *LED_PORT = *LED_PORT | (1U << 3); 
    ```
  * *Example: Set bit 3 LOW (AND operation)*
    ```C
    *LED_PORT = *LED_PORT & (~(1U << 3));
    ```

---

### **7. SDCC Specific Constraints**

*Rationale: SDCC is a great compiler, but it has quirks tailored for 8-bit systems.*

* **Rule 7.1: Declare variables at the top of the scope.**
  * **General Rule:** Declare variables at the start of the function block. SDCC generally produces more efficient code with this structure.
  * **Exception:** You are permitted to declare loop iterators inside the `for` loop definition to limit their scope.
  * *Example:* `for (uint8_t i = 0; i < 10; i = i + 1) { ... }`
* **Rule 7.2: Global variables for large arrays.**
  * Large arrays must be `static` or global to avoid stack overflow.
* **Rule 7.3: Do not use in-line assembly `__asm__(...)`, except `__asm__("nop");`.**

---

### **8. Operator Use & Clarity**

*Rationale: Explicit operations prevent code ambiguity and eliminate subtle operator side-effects.*

* **Rule 8.1: Prohibit In-Line Composite Manipulation.**
  * Never use compound assignment operators (`+=`, `-=`, `^=`, `&=`, `|=`, `<<=`, etc.) or increment/decrement (`++`, `--`).
  * **Why:** The long form is clearer and prevents side-effect bugs.
  * *Example:*
    ```C
    // BAD:  d++;
    // GOOD: d = d + 1;

    // BAD:  m <<= 2;
    // GOOD: m = m << 2;

    // BAD:  k ^= 0x80U;
    // GOOD: k = k ^ 0x80U;
    ```

---

### **Sample "Perfect" Student Code**

The template to demonstrate the guidelines in action:

```C
/*
 * Hardware: Z80 simulated with memory mapped LED at 0x8000
 * Goal: Blink LED
 */

#include <stdint.h>
#include <stdbool.h>

// Define hardware address (Memory Mapped IO)
// Rule 3.2: Combined pointer macro with U suffix
// Rule 1.1: U suffix prevents signed integer interpretation
#define IO_LED       ((volatile uint8_t *) 0x8000U)

void delay_loops(uint16_t count) {
    while (count > 0) {
        // Use explicit subtraction (Rule 8.1)
        count = count - 1; 

        // Rule 7.3: Use __asm__("nop") to delay
        __asm__("nop");
    }
}

void main(void) {
    uint8_t pattern = 0x01U;

    // Rule 5.2: Infinite Super Loop
    while (true) {
        // 1. Write to Data Bus
        *IO_LED = pattern;

        // 2. Wait
        delay_loops(5000U);

        // 3. Logic: Shift pattern left
        if (pattern == 0x80U) {
            pattern = 0x01U;
        } else {
            // Use explicit shift (Rule 8.1)
            pattern = pattern << 1;
        }
    }
}
```

---

### **9. Read the `C99 Style Guide`**

**Read** the [**C99 Style Guide**](./C99-style-guide.md) next.
