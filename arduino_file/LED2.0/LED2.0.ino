#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LedControl.h>


#define DIN D5
#define CS D6
#define CLK D7

const char* ssid = "BlackWalnut";
const char* password = "blackwalnut";
const char* mqtt_server = "47.102.101.77";
const char* mqtt_username = "user";
const char* mqtt_password = "123456";

byte one[8] = {0, 0, 0, 24, 24, 0, 0, 0};
byte two[8] = {B00000000, B11000000, B11000000, B00000000, B00000000, B00000011, B00000011, B00000000};
byte three[8] = {B00000000, B11000000, B11000000, B00011000, B00011000, B00000011, B00000011, B00000000};
byte four[8] = {B00000000, B11000011, B11000011, B00000000, B00000000, B11000011, B11000011, B00000000};
byte five[8] = {B00000000, B11000011, B11000011, B00011000, B00011000, B11000011, B11000011, B00000000};
byte six[8] = {B00000000, B11011011, B11011011, B00000000, B00000000, B11011011, B11011011, B00000000};

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long delaytime = 1000;
  LedControl lc = LedControl(DIN, CLK, CS, 1);


void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  client.connect(mqtt_server, mqtt_username, mqtt_password);

  client.setCallback(callback);
  client.subscribe("controlLED");
  client.subscribe("LEDfiles");


  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);
  delay(100);
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
void writeArduinoOnMatrix(int digit = 0) {
  switch (digit) {
    case 0: break;
    case 1: show(one); break;
    case 2: show(two); break;
    case 3: show(three); break;
    case 4: show(four); break;
    case 5: show(five); break;
    case 6: show(six); break;
    default: break;
  }
}
void show(byte _get[]) {
  lc.clearDisplay(0);
  lc.setRow(0, 0, _get[0]);
  lc.setRow(0, 1, _get[1]);
  lc.setRow(0, 2, _get[2]);
  lc.setRow(0, 3, _get[3]);
  lc.setRow(0, 4, _get[4]);
  lc.setRow(0, 5, _get[5]);
  lc.setRow(0, 6, _get[6]);
  lc.setRow(0, 7, _get[7]);
  delay(delaytime);

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  if (strcmp(topic, "controlLED") == 0) {
    int num = (int)((char)payload[0]) - 48;
    Serial.println(num);
    writeArduinoOnMatrix(num);
    Serial.println();
  }
  else if (strcmp(topic, "LEDfiles") == 0) {
    switch (payload[0] - 48) {
      case (1): changeLED(one, payload); writeArduinoOnMatrix(1); break;
      case (2): changeLED(two, payload); writeArduinoOnMatrix(2); break;
      case (3): changeLED(three, payload); writeArduinoOnMatrix(3); break;
      case (4): changeLED(four, payload); writeArduinoOnMatrix(4); break;
      case (5): changeLED(five, payload); writeArduinoOnMatrix(5); break;
      case (6): changeLED(six, payload); writeArduinoOnMatrix(6); break;
      default: break;
    }
  }

}
void changeLED(byte _get[], byte* input) {
  int num = 0;
  int temp = 0;
  //  for (int cnt = 1; cnt <= 64; ) {
  //    num = 0;
  //    for (int ccnt = 0; ccnt < 8; ccnt++, cnt++) {
  //      num = num + (input[cnt] - 48) * pow(2, 7 - ccnt);
  //    }
  //    _get[temp] = num;
  //    temp++;
  //  }
  for (int cnt = 2;; cnt++) {
    num = 0;
    for (int ccnt = cnt;; ccnt++,cnt++) {
      if (input[cnt] == ',' || input[cnt] == '\0') {
        break;
      }
      num = num * 10 + input[cnt] - 48;
    }
    
    _get[temp] = num;
    temp++;
    if (input[cnt] == '\0') {
      break;
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-0000";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
//  LedControl lc = LedControl(DIN, CLK, CS, 1);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  writeArduinoOnMatrix(0);

}
