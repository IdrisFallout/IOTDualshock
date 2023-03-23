#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <SoftwareSerial.h>
#include "credentials.h"

const int port = 80;

SoftwareSerial mySerial(D7, D8); // RX, TX

WiFiServer server(port);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  IPAddress staticIP(192, 168, 1, 110); //replace with the IP address you want to use
  IPAddress gateway(192, 168, 1, 1); //replace with the gateway IP address of your network
  IPAddress subnet(255, 255, 255, 0); //replace with the subnet mask of your network
  WiFi.config(staticIP, gateway, subnet); // configure the WiFi with the static IP address
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.begin();
  Serial.println("Server started");
}

void loop() {
  client = server.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      while (client.available()) {
        String message = client.readStringUntil('\n');
        Serial.print("Received message: ");
        mySerial.println(message);
        Serial.println(message);
      }
    }

    Serial.println("Client disconnected");
  }
}