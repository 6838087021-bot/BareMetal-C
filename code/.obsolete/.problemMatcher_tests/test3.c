/* test-include.c */
#include "non_existent_header.h" 
// Error: usually "file not found" or syntax error depending on sdcpp version
// This confirms if the regex handles "fatal error" or generic include errors.

void main(void) {}
