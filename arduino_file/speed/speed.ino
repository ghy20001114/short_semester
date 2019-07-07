
#include <SoftwareSerial.h>

SoftwareSerial mpu6050(D3, D4); // RX,TX


void setup() {

  Serial.begin(9600);
  mpu6050.begin(115200);
  //  mpu6050.write(0x52);
  Serial.println("-------------- done --------------");

}

unsigned char AxL;
unsigned char AxH;
unsigned char AyL;
unsigned char AyH;
unsigned char AzL;
unsigned char AzH;
unsigned char TL;
unsigned char TH;
unsigned char Sum;


void loop()
{
  byte s;
  double ax, ay, az;
  int tmp;

  int b = mpu6050.read();
  //  Serial.println(b);
  if (b == 0x55)
  {
    int a = mpu6050.read();
    //        Serial.println(a);
    switch (a)
    {
      case 0x51: AxL = mpu6050.read();
        Serial.print("AxL:"); Serial.println(AxL);

        AxH = mpu6050.read();
        Serial.print("AxH:"); Serial.println(AxH);

        AyL = mpu6050.read();
//        Serial.print("AyL:"); Serial.println(AyL);

        AyH = mpu6050.read();
//        Serial.print("AyH:"); Serial.println(AyH);
        AzL = mpu6050.read();
        AzH = mpu6050.read();
        //        Serial.print("AzH:"); Serial.println(AzH);

        TL = mpu6050.read();
        //                Serial.print("TL:");Serial.println(TL);

        TH = mpu6050.read();
        Sum = mpu6050.read();
        Serial.println(Sum);
        ax = (short(AxH << 8 | AxL)) / 32768.0 * 16 ;
//        Serial.print( "                ax:"); Serial.println(ax, 6);


        ay = (short(AyH << 8 | AyL)) / 32768.0 * 16 ;
        Serial.print( "                ay:"); Serial.println(ay, 6);

        az = (short(AzH << 8 | AzL)) / 32768.0 * 16 ;
        s = 85 + 81 + AxH + AxL + AyH + AyL + AzH + AzL + TL + TH;
        //        s = s & 0xFF;
        if (Sum == s) {
          //          if (ax != 0) {
          //            client.publish("touch", "change");
          //            delay(1000);
          //            mpu6050.flush();
          //          }
          Serial.println("11111111111");
        } else {
          break;
        }
        break;
      case 0x52: break;
      case 0x53: break;
    }
  }
  else
  {
    //      Serial.print("Now Len Are: ");Serial.println(mpu6050.available());

    //    mpu6050.flush();
  }

}
