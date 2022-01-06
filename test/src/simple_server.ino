//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Adafruit_Sensor.h>
#include <dht.h>
//#include <FS.h>

AsyncWebServer server(80);

const char* ssid = "wifi";
const char* password = "0700848237";

const char* PARAM_MESSAGE = "message";

#define DHTPIN 4
#define DHTTYPE 22
DHT dht(DHTPIN, DHTTYPE);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
String temp() {
  float t = dht.readTemperature();
  String value;
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    value = String(0);
  }
  else{
      value = String(t);
  }
 return value;
}

void writeTemperature(){
  File file = LittleFS.open("/temp.txt", "w");
  String value = temp();
 
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
 
file.print(value);
    Serial.write(file.read());
  file.close();
}

void setup() {

    Serial.begin(9600);
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    if(!LittleFS.begin()){
        Serial.println("Failed to start File System");
        return;
    }
    //writeTemperature();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css");
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/script.js", "text/javascript");
    });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
}