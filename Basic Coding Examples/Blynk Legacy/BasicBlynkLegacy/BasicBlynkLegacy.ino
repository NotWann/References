//Blynk Legacy basic coding:

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

char auth[] = "  "; // Auth token
char ssid[] = "  "; // WiFi ssid
char pass[] = "  "; // WiFi password

char server[] = "prakitblog.com"; // Custom server
int port = 8181;  // port can be different


// Blynk display to Blynk Apps function
Blynk.virtualWrite(V0, "HELLO WORLD");
Blynk.virtualWrite(V1, String(percentage), 2); // --> 2 decimal point, convert to string first.

// Blynk read to Blynk Apps function
BLYNK_WRITE(V2)
{
  int buzzer = 2;
  buttonPressed = param.asInt();
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void connectToBlynk()
{
  unsigned long start = millis();
  while (!Blynk.connected() && millis() - start < 10000)  // 10 seconds timeout
  {
    Blynk.run()
    delay(1000);
  }
  if (Blynk.connected()) 
  {
    Serial.println("Blynk Connected!");
  }
  else 
  {
    Serial.println("Blynk connection failed!");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, server, port);  // Initialize blynk config
}

void loop()
{
  if (!Blynk.connected()) 
  {
    Serial.println("Blynk disconnected! Reconnecting...");
    connectToBlynk();
  }
  Blynk.run();

  delay(10);
}