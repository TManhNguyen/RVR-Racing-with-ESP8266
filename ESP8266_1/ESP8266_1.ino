/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLZ_Kd3SO6"
#define BLYNK_DEVICE_NAME "RVR Racing Robot"
#define BLYNK_AUTH_TOKEN "CH6SFZ9qtEWXH35nM7o7QXReQYzGSv10"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Hotspotify";
char pass[] = "huhuhuhu";

int x;
int y;
int z;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

BLYNK_WRITE(V0)
{
  if (0 <= param.asInt() && param.asInt() <= 100) {
    x = param.asInt();
    if (35 <= x && x <= 65) {
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
    }    if (10 <= x && x < 35) {
      Serial.println("Left");
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
    }    if (65 < x && x <= 90) {
      Serial.println("Right");
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
    } if (0 <= x && x < 10) {
      Serial.println("MaxLeft");
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
    } if (90 < x && x <= 100) {
      Serial.println("MaxRight");
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
    } 
  }
}

BLYNK_WRITE(V1)
{
  y = param.asInt();
  if (y == 50 && y == 50) {
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
  } if (y < 50) {
    digitalWrite(D0, HIGH);
    digitalWrite(D1, LOW);
  } if (y > 50) {
    digitalWrite(D0, LOW);
    digitalWrite(D1, HIGH);
  }
}
BLYNK_WRITE(V2)
{
  z = param.asInt();
  if (z == 1) {
    digitalWrite(D0, HIGH);
    digitalWrite(D1, HIGH);
    delay(1000);
    digitalWrite(D0, LOW);
    digitalWrite(D1, HIGH);
    Blynk.virtualWrite(V2, 0);
  }
}
BLYNK_WRITE(V3)
{
  z = param.asInt();
  if (z == 1) {
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    delay(100);
  }
}


void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
