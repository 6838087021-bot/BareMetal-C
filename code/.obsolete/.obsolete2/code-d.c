#define LOCA 0x8000U
#define LOCB 0x8001U
#define DISP 0x8002U
// I/O address from 4000 to 7FFF
#define LED   0x4000U
#define DIPSW 0x4001U
#define SEVEN 0x6000U

void main(void) {
  unsigned char i;
  unsigned char x = 1;
  unsigned char y = 0;
  unsigned char d;

  const unsigned char seg7_table[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;
  unsigned char *led = (volatile unsigned char *) LED;
  unsigned char *dipsw = (volatile unsigned char *) DIPSW;
  unsigned char *disp = (volatile unsigned char *) DISP;
  unsigned char *seven = (volatile unsigned char *) SEVEN;

  for(;;) {
    *loca = x;
    *(seven+2) = seg7_table[x & 0x0F];
    *(seven+3) = seg7_table[x >> 4];
    x++;
    for (i = 0; i < 3; i++) {
      *locb = y;
      d = *dipsw;
      *disp = d;
      *led = d;
      *seven = seg7_table[y & 0x0F];
      *(seven+1) = seg7_table[y >> 4];
      y++;
    }
  }

}
