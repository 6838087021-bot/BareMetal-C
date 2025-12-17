#define LOCA 0x8000U
#define LOCB 0x8001U
#define LOCM 0x8010U
#define PUSHBUTTON 0x5000U

void main(void) {
  unsigned char x = 1;
  unsigned char y = 0;
  unsigned int pos = 0;
  
  unsigned char *loca = (volatile unsigned char *) LOCA;
  unsigned char *locb = (volatile unsigned char *) LOCB;
  unsigned char *locm = (volatile unsigned char *) LOCM;
  unsigned char *pushbutton = (volatile unsigned char *) PUSHBUTTON;
  unsigned char b;

  for(;;) {
    *loca = x++;
    b = *pushbutton;
    if (b) {
      *locb = y++;
      b = b & 0x7F;
      *(locm + pos++) = b;
    }
  }
}

/*

i1|i3|i5|i7|i9|i11|i13|i15|i17|i19|i21|i23|i25|i27|i29|i31
i2|i3|i6|i7|i10|i11|i14|i15|i18|i19|i22|i23|i26|i27|i30|i31
i4|i5|i6|i7|i12|i13|i14|i15|i20|i21|i22|i23|i28|i29|i30|i31
i8|i9|i10|i11|i12|i13|i14|i15|i24|i25|i26|i27|i28|i29|i30|i31
i16|i17|i18|i19|i20|i21|i22|i23|i24|i25|i26|i27|i28|i29|i30|i31
i0|i1|i2|i3|i4|i5|i6|i7|i8|i9|i10|i11|i12|i13|i14|i15|i16|i17|i18|i19|i20|i21|i22|i23|i24|i25|i26|i27|i28|i29|i30|i31

*/
