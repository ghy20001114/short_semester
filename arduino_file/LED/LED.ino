#include <LedControl.h>

#define DIN D5
#define CS D6
#define CLK D7

LedControl lc=LedControl(DIN,CLK,CS,1);

unsigned long delaytime=1000;

void setup() {

  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  delay(100);
}

void writeArduinoOnMatrix() {
  byte one[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
  byte two[8]={B00000000,B11000000,B11000000,B00000000,B00000000,B00000011,B00000011,B00000000};
  byte three[8]={B00000000,B11000000,B11000000,B00011000,B00011000,B00000011,B00000011,B00000000};
  byte four[8]={B00000000,B11000011,B11000011,B00000000,B00000000,B11000011,B11000011,B00000000};
  byte five[8]={B00000000,B11000011,B11000011,B00011000,B00011000,B11000011,B11000011,B00000000};
  byte liu[8]={B00000000,B11011011,B11011011,B00000000,B00000000,B11011011,B11011011,B00000000};

  lc.setRow(0,0,liu[0]);
  lc.setRow(0,1,liu[1]);
  lc.setRow(0,2,liu[2]);
  lc.setRow(0,3,liu[3]);
  lc.setRow(0,4,liu[4]);
  lc.setRow(0,5,liu[5]);
  lc.setRow(0,6,liu[6]);
  lc.setRow(0,7,liu[7]);
  delay(delaytime);
  lc.clearDisplay(0);

  lc.setRow(0,0,five[0]);
  lc.setRow(0,1,five[1]);
  lc.setRow(0,2,five[2]);
  lc.setRow(0,3,five[3]);
  lc.setRow(0,4,five[4]);
  lc.setRow(0,5,five[5]);
  lc.setRow(0,6,five[6]);
  lc.setRow(0,7,five[7]);
  delay(delaytime);
  lc.clearDisplay(0);

  lc.setRow(0,0,four[0]);
  lc.setRow(0,1,four[1]);
  lc.setRow(0,2,four[2]);
  lc.setRow(0,3,four[3]);
  lc.setRow(0,4,four[4]);
  lc.setRow(0,5,four[5]);
  lc.setRow(0,6,four[6]);
  lc.setRow(0,7,four[7]);
  delay(delaytime);
  lc.clearDisplay(0);
  
  lc.setRow(0,0,three[0]);
  lc.setRow(0,1,three[1]);
  lc.setRow(0,2,three[2]);
  lc.setRow(0,3,three[3]);
  lc.setRow(0,4,three[4]);
  lc.setRow(0,5,three[5]);
  lc.setRow(0,6,three[6]);
  lc.setRow(0,7,three[7]);
  delay(delaytime);
  lc.clearDisplay(0);
  lc.setRow(0,0,two[0]);
  lc.setRow(0,1,two[1]);
  lc.setRow(0,2,two[2]);
  lc.setRow(0,3,two[3]);
  lc.setRow(0,4,two[4]);
  lc.setRow(0,5,two[5]);
  lc.setRow(0,6,two[6]);
  lc.setRow(0,7,two[7]);
  delay(delaytime);
  lc.clearDisplay(0);
  lc.setRow(0,0,one[0]);
  lc.setRow(0,1,one[1]);
  lc.setRow(0,2,one[2]);
  lc.setRow(0,3,one[3]);
  lc.setRow(0,4,one[4]);
  lc.setRow(0,5,one[5]);
  lc.setRow(0,6,one[6]);
  lc.setRow(0,7,one[7]);
  delay(delaytime);
  lc.clearDisplay(0);

}

void loop() { 
  writeArduinoOnMatrix();

}
