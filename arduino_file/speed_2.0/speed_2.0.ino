
#include <SoftwareSerial.h>

SoftwareSerial mpu6050(D3, D4); // RX,TX

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "BlackWalnut";
const char* password = "blackwalnut";
const char* mqtt_server = "47.102.101.77";
const char* mqtt_username = "user";
const char* mqtt_password = "123456";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  // We start by connecting to a WiFi network
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

void setup() {

  Serial.begin(9600);
  mpu6050.begin(115200);
  //  mpu6050.write(0x52);
  Serial.println("-------------- done --------------");
  setup_wifi();

  client.setServer(mqtt_server, 1883);

  client.connect(mqtt_server, mqtt_username, mqtt_password);

//    client.setCallback(callback);
    client.subscribe("mqtt");

}





byte AxL;
byte AxH;
int AyL;
int AyH;
int AzL;
int AzH;
int TL;
int TH;
int Sum;


void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int ax, ay, az, s;
  int tmp;

  int b = mpu6050.read();
//Serial.println(b);
  if (b == 0x55)
  {
    int a = mpu6050.read();
//    Serial.println(a);
    switch (a)
    {
      case 0x51: AxL = mpu6050.read();
        Serial.print("AxL:"); Serial.println(AxL);

        AxH = mpu6050.read();
        Serial.print("AxH:"); Serial.println(AxH);


        AyL = mpu6050.read();
        Serial.print("AyL:"); Serial.println(AyL);


        AyH = mpu6050.read();
        Serial.print("AyH:"); Serial.println(AyH);
        AzL = mpu6050.read();
        AzH = mpu6050.read();
        Serial.print("AzH:"); Serial.println(AzH);

        TL = mpu6050.read();
        //                Serial.print("TL:");Serial.println(TL);

        TH = mpu6050.read();
        Sum = mpu6050.read();
        Serial.println(Sum);
        ax = ((AxH << 8) | AxL) / 32768 * 16 * 9.8;
        Serial.print("ax:"); Serial.println(ax);


        ay = ((AyH << 8) | AyL) / 32768 * 16 * 9.8;
        az = ((AzH << 8) | AzL) / 32768 * 16 * 9.8;
        s = 85 + 81 + AxH + AxL + AyH + AyL + AzH + AzL + TL + TH;
        s = s & 0xFF;
        if (Sum == s) {
          if (ax != 0) {
            client.publish("touch", "change");
            delay(1000);
            mpu6050.flush();

          }
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

    mpu6050.flush();
  }

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-000000";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
