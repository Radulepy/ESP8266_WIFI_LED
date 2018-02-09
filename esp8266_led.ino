#include <ESP8266WiFi.h>
#define RELAY_PIN D1
const char* password = "insert WIFI password";
const char* ssid = "insert WIFI SSID";
const int port = 8181;
/// YOU CAN DOWNLOAD 'PUTTY' SOFTWARE FOR COM PORT COMUNICATION - SEND 1 TO TURN ON LED / O, TO TURN OFF
WiFiServer server(port);

void setup() {
  pinMode(1, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  while(client.connected()) {
    if (client.available()) {
      uint8_t buf;
      size_t length = 1;
      client.read(&buf, length);
      client.write(handleCmd(buf));
    }
  }
}

char* handleCmd(uint8_t cmd) {
  Serial.println(cmd);
  switch(cmd) {
    case 49:
        digitalWrite(1, HIGH);
        return "Relay pin set to high\n";
    case 48:
        digitalWrite(1, LOW);
        return "Relay pin set to low\n";
    case 10:
        digitalWrite(1, HIGH);
        return "Relay pin set to high\n";
    case 13:
        digitalWrite(1, LOW);
        return "Relay pin set to low\n";
    default:
        return "Send ASCII 1 for on, and 0 for off.\n";
  }
}
