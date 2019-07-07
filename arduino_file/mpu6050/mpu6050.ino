#include<SoftwareSerial.h>
#include <ArduinoJson.h>
unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;
double RwAcc[3], w[3], Gyro[3], T, RwGyro[3], Awz[2], RwEst[3];
byte A[11];
String gy;
const char *p[100];

int lastTime = 0;
float wGyro = 10.0;
int  interval = 0;

SoftwareSerial ss(D3, D4); //RX TX

long lastMsg = 0;
char msg[50];
int value = 0;
double msg1;

void setup() {

  Serial.begin(9600);
  ss.begin(115200);

}




void publishData(float ax, float ay, float az, float anglex, float angley) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["ax"] = (String)ax;
  root["ay"] = (String)ay;
  root["az"] = (String)az;
  root["gx"] = (String)anglex;
  root["gy"] = (String)angley;
  root.prettyPrintTo(Serial);
  char data[500];
  root.printTo(data, root.measureLength() + 1);

}

void normalize3DVec(double vector0, double vector1, double vector2)
{
  float r;
  r = sqrt(vector0 * vector0 + vector1 * vector1 + vector2 * vector2);
  vector0 /= r;
  vector1 /= r;
  vector2 /= r;
}

void getInclination() {
  int w = 0;
  float tmpf = 0.0;
  int currentTime, signRzGyro;
  normalize3DVec(RwAcc[0], RwAcc[1], RwAcc[2]);
  currentTime = millis();
  interval = currentTime - lastTime;
  lastTime = currentTime;
  for (w = 0; w <= 2; w++) {
    RwEst[w] = RwAcc[w];
  }
  if (abs(RwEst[2]) < 0.1) {
    for (w = 0; w <= 2; w++)
    {
      RwGyro[w] = RwEst[w];
    }
  }
  else {
    for (w = 0; w <= 1; w++)
    {
      tmpf = Gyro[w];
      tmpf *= interval / 1000.0f;
      Awz[w] = atan2(RwEst[w], RwEst[2]) * 180 / PI;
      Awz[w] += tmpf;
    }
  }
}


void read() {
  while (ss.available()) {
    Re_buf[counter] = (unsigned char)ss.read();
    if (counter == 0 && Re_buf[0] != 0x55) return;
    counter++;
    if (counter == 11)
    {
      counter = 0;
      sign = 1;
    }

    if (sign)
    {
      sign = 0;
      if (Re_buf[0] == 0x55)   //���֡ͷ
      {
        switch (Re_buf [1])
        {
          case 0x51:
            RwAcc[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 16;
            Serial.println(RwAcc[0]);
            RwAcc[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 16;
            RwAcc[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 16;
            T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
            break;
          case 0x52:
            w[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 2000;
            w[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 2000;
            w[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 2000;
            T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
            break;
          case 0x53:
            Gyro[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
            Gyro[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
            Gyro[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
            if (Gyro[0] < 2 && Gyro[0] > -2) return;
            if (Gyro[1] < 2 && Gyro[1] > -2) return;
            if (Gyro[2] < 2 && Gyro[2] > -2) return;
            getInclination();
            
            long now = millis();
            if (now - lastMsg > 100) {
              lastMsg = now;
              ++value;
              publishData(RwAcc[0], RwAcc[1], RwAcc[2], Awz[0], Awz[1]);
            }
            A[0] = 0;
            delay(50);
            break;
        }
      }
    }
  }
}


void loop() {
  read();
}
