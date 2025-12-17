#include <LiquidCrystal_AIP31068_I2C.h>

#define B_CLK 0x4000
#define B_ROW 0x0180
#define B_COL 0x3E00

// I2C address = 0x3E , 20x4 display
LiquidCrystal_AIP31068_I2C lcd( 0x3E, 20, 4 );

void setup() {
  for (int i=0; i<=14; ++i) pinMode(i,INPUT_PULLUP);
  lcd.init();
  }

void loop() {
  uint16_t k=1,d=0;
  static uint16_t dOld=d;
  // Read digital input into the 16-bit "d" 
  if (digitalRead(14)) d|=B_CLK;
  if (((dOld&B_CLK)==0) && ((d&B_CLK)!=0)) {
    for (int i=0; i<=14; ++i) {
      if (digitalRead(i)) d|=k;
      k=k<<1; 
      }
    if ((d&B_CLK)!=0) {
      lcd.setCursor((d&B_COL)>>9,(d&B_ROW)>>7);
      char str[2]="\x0";
      str[0]=d&0x7F;
      lcd.print(str);
      } else {
      // Miss
      }
    }
  dOld=d;
  }
