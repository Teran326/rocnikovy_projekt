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
//#include <LittleFS.h>
#include <Adafruit_Sensor.h>
#include <FS.h>

AsyncWebServer server(80);

const char* ssid = "AndroidAP_8064";
const char* password = "something";

const char* PARAM_MESSAGE = "message";

const long duration = 5000;
long rememberTime=0;

//#define DHTPIN 4
//#define DHTTYPE 22
//DHT dht(DHTPIN, DHTTYPE);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void write(){
    File file = SPIFFS.open("/data.txt", "w");
    file.close();
}

void append(){
    File file = SPIFFS.open("/data.txt", "a");
    file.print("temperature ");
    file.close();
}

void read(){
    File file = SPIFFS.open("/data.txt", "r");
    while(file.available()){
        Serial.write(file.read());
    }
    Serial.println();
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
    if(!SPIFFS.begin()){
        Serial.println("Failed to start File System");
        return;
    }
    String str = "";
Dir dir = SPIFFS.openDir("/");
while (dir.next()) {
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
}
Serial.print(str);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "text/javascript");
    });
    server.on("/readADC", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/data.txt", "text/plain");
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
    write();

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
    if( (millis()- rememberTime) >= duration){   
    append();
    read();// change the state of LED
    rememberTime=millis();// remember Current millis() time
    }
}