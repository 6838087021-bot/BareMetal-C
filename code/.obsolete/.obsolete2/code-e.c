#define LOCA 0x8000U
#define LOCB 0x8001U
#define PUSHBUTTON 0x5000U

void main(void) {
  unsigned char x = 1;
  unsigned char y = 0;
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;
  unsigned char *pushbutton = (volatile unsigned char *) PUSHBUTTON;
  unsigned char b;

  for(;;) {
    *loca = x++;
    b = *pushbutton;
    if (b) {
      *locb = y++;
    }
  }
}
