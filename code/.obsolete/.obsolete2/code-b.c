#define LOCA 0x8000U
#define LOCB 0x8001U
// I/O address from 4000 to 7FFF
#define LED  0x4000U

void main(void) {
  unsigned char i;
  unsigned char x = 1;
  unsigned char y = 0;
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;
  unsigned char *led = (volatile unsigned char *) LED;

  /*
  for(;;) {
      *led = 0x55;
  }
  */

  for(;;) {
    *loca = x++;
    for (i = 0; i < 3; i++) {
      *locb = y++;
      *led = y;
    }
  }

}
