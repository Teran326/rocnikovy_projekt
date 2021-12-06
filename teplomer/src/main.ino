#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SimpleTime.h>
 
const char* ssid = "wifi";
const char* password = "0700848237";
const int pin = 17;
int sensorValue;
int i = 0;
 
ESP8266WebServer server(80);
 
// Serving Hello world




void teplota(){
    /*time_t cas = time(system_get_time());
    int hodina = hour(cas);
    int minuta = minute(cas);
    int den = day(cas);
    int mesic = month(cas);
    int rok = year(cas);
    String datum = "";
    datum += den;
    datum += ".";
    datum += mesic;
    datum += ".";
    datum += rok;
    datum += " ";
    datum += hodina;
    datum += ":";
    datum += minuta;*/
    sensorValue = analogRead(pin);
    String data = "";
    data += sensorValue;
    //server.send(200, "text/plain", datum);
    server.send(200, "text/plain", data);
}
 
// Define routing
void restServerRouting() {
  server.on("/", HTTP_GET, teplota);
}
 
// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void) {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 
  // Set server routing
  
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
  restServerRouting();
  delay(2000);
}