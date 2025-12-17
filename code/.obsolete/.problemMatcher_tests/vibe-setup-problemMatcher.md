# Setting up "patternMatcher" for `.vscode/settings.json`
Code is always compiled with:
```bash
sdcc -mz80 --std c99 --Werror -c source.c -o source.rel
```
unless noted.

---

## Code 1: misspelling __critical and __interrupt
```C
#include <stdbool.h>
#include <stdint.h>

#define ADDR0 0x0060U
#define ADDR1 0x0062U
#define NMI_COUNT 0x0064U

void nmi_isr(void) __critica __interrup {
  uint8_t *count = (volatile uint8_t *) NMI_COUNT;
  uint8_t v = *count;

  *count = *count + 1;
}

void main(void) {
  uint8_t *count0 = (volatile uint8_t *) ADDR0;
  uint8_t *count1 = (volatile uint8_t *) ADDR1;

  *count0 = 0;
  *count1 = 0;

  while (true) {
    for (uint8_t i = 0; i < 3; i = i + 1) {
      *count1 = *count1 + 1;
    }
    *count0 = *count0 + 1;
  }
}
```
SDCC Output:
```
test1.c:11: syntax error: token -> '__critica' ; column 28
```

## Code 2: undeclared variable i
```
/* test-warning.c */
#include <stdint.h>

void main(void) {
    i = 10; 
    // Error: warning 85: in function main unreferenced local variable : 'i'
}
```
SDCC Output:
```
test2.c:5: error 20: Undefined identifier 'i'
```

## Code 3: include nonexistent header
```
/* test-include.c */
#include "non_existent_header.h" 
// Error: usually "file not found" or syntax error depending on sdcpp version
// This confirms if the regex handles "fatal error" or generic include errors.

void main(void) {}
```
SDCC Output:
```
test3.c:2:10: fatal error: non_existent_header.h: No such file or directory
    2 | #include "non_existent_header.h"
      |          ^~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
test3.c:1: error 190: ISO C forbids an empty translation unit
subprocess error 256
```

## Code 4: multiple definitions
```
/* test-dup.c */
void my_func(void) {}
void my_func(void) {} // Error: multiple definition

void main(void) {
    my_func();
}
```
SDCC Output:
```
test4.c:3: error 65: function 'my_func' already has body
```

## Code 5: missing ;
```
/* test-syntax.c */
void main(void) {
    int a = 5
    int b = 6; // Missing semicolon above usually flags error here or line before
}
```
SDCC Output:
```
test5.c:4: syntax error: token -> 'int' ; column 7
```

## Code 6: missing linking function

```
/* test-link.c */
void missing_function(void); // Declared but never defined

void main(void) {
    missing_function();
}
```
compiled with:
```
sdcc -mz80 --std c99 --Werror test6.c
```
SDCC Output:
```

?ASlink-Warning-Undefined Global '_missing_function' referenced by module 'test6'
```
**note:** there is an empty line before `?ASlink-Warning-Undefined Global '_missing_function'`

## Code 7: inline assembly -- value too large for register
```
/* test-asm.c */
void main(void) {
    __asm
        ld a, #0x10000
    __endasm;
}
```
SDCC Output:
- blank. no error.

## Code 8: inline assembly -- invalid opcode
```
/* test-asm.c */
void main(void) {
    __asm
        invalid_opcode
    __endasm;
}
```
SDCC Output:
```
test8.asm:50: Error: <o> .org in REL area or directive / mnemonic error
removing test8.rel
```

## Code 9: macro expansion error
```
// macro expansion error
#define BAD_MACRO(x)  (x + ; ) // Syntax error inside macro
void main(void) {
    int i = BAD_MACRO(5);
}
```
SDCC Output:
```
test9.c:4: syntax error: token -> ';' ; column 18
```

## Code 10: Integer Promotion / Overflow Warning
```
// Integer Promotion / Overflow Warning
void main(void) {
    unsigned char a = 200;
    unsigned char b = 100;
    if (a + b > 300) {} // 8-bit overflow before comparison?
}
```
SDCC Output:
- no error

## Code 11: Invalid pragmas
```
#pragma non_existent_pragma
void main(void) { int i = 3; }
```
SDCC Output:
```
test11.c:1: error 190: ISO C forbids an empty translation unit
```

## Code 12: invalid header
`test12.h`:
```
/* bad_header.h */
int 5; // Syntax error
```
`test12.c`:
```
/* test-header.c */
#include "test12.h"
void main(void) {}
```
SDCC Output:
```
test12.h:2: syntax error: token -> '5' ; column 5
```

## Code 13: duplicate case
```
// duplicate case
void main(void) {
    int i = 1;
    switch(i) {
        case 1: break;
        case 1: break; // Duplicate
    }
}
```
SDCC Output:
```
test13.c:5: error 56: Duplicate label 'case'
```

## Code 14: Array Initialization Size Mismatch
```
void main(void) {
    char str[3] = "Hello"; // Too long
}
```
SDCC Output:
```
test14.c:2: error 147: excess elements in string initializer after 'str'
```

## Code 15: Memory Overflow (Linker Error)
```
/* test-overflow.c */
// Allocating 50KB array in a 64KB Z80 space (might clash with code/stack)
unsigned char huge_data[65530]; 

void main(void) {
    huge_data[0] = 1;
}
```
compiled with:
```
sdcc -mz80 --std c99 --Werror test15.c
```
SDCC Output:
- no error

## Code 16: Const/Volatile Qualifier Mismatch
```
/* test-qualifier.c */
#include <string.h>
void main(void) {
    volatile char *hw_register = (char*)0x8000;
    // Warning: passing 'volatile char *' to parameter of type 'const char *'
    size_t len = strlen(hw_register); 
}
```
SDCC Output:
- no error

---

- Help me set up "problemMatcher" for `sdcc`. it's very different than `gcc`
- suggest codes to try to discover more for "problemMatcher"