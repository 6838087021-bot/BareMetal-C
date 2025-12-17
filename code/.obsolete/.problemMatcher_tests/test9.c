// macro expansion error
#define BAD_MACRO(x)  (x + ; ) // Syntax error inside macro
void main(void) {
    int i = BAD_MACRO(5);
}
