#define LOCA 0x8000U
#define LOCB 0x8001U
#define DISP 0x8002U
// I/O address from 4000 to 7FFF
#define LED   0x4000U
#define DIPSW 0x4001U

void main(void) {
  unsigned char i;
  unsigned char x = 1;
  unsigned char y = 0;
  unsigned char d;
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;
  unsigned char *led = (volatile unsigned char *) LED;
  unsigned char *dipsw = (volatile unsigned char *) DIPSW;
  unsigned char *disp = (volatile unsigned char *) DISP;

  for(;;) {
    *loca = x++;
    for (i = 0; i < 3; i++) {
      *locb = y++;
      d = *dipsw;
      *disp = d;
      *led = d;
    }
  }

}
