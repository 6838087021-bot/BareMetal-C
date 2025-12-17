// Integer Promotion / Overflow Warning
void main(void) {
    unsigned char a = 200;
    unsigned char b = 100;
    if (a + b > 300) {} // 8-bit overflow before comparison?
}
