#define LOCA 0x8000U
#define LOCB 0x8001U

void main(void) {
  unsigned char i;
  unsigned char x = 1;
  unsigned char y = 0;
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;

  for(;;) {
    *loca = x++;
    for (i = 0; i < 3; i++) {
      *locb = y++;
    }
  }
}
