/* test-dup.c */
void my_func(void) {}
void my_func(void) {} // Error: multiple definition

void main(void) {
    my_func();
}
