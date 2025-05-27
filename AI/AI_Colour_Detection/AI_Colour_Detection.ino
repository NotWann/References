#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "Redmi 14C";  // Change this
const char* password = "abc9519992#";  // Change this

WebServer server(8080);  // Create a web server on port 80

const int LED_PIN = 2;  // Change to your LED pin

void handleRoot() {
  server.send(200, "text/plain", "ESP32 LED Controller");
}

void handleControl() {
  if (server.hasArg("led")) {
    String ledState = server.arg("led");
    if (ledState == "on") {
      digitalWrite(LED_PIN, HIGH);
    } else if (ledState == "off") {
      digitalWrite(LED_PIN, LOW);
    }
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(LED_PIN, OUTPUT);
  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.begin();
}

void loop() {
  server.handleClient();
}
