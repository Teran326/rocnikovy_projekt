#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LittleFS.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

AsyncWebServer server(80);

IPAddress ip(10, 0, 1, 200);
IPAddress dns(8, 8, 8, 8);
IPAddress gateway(10, 0, 1, 138);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "wifi";
const char* password = "0700848237";

const char* PARAM_MESSAGE = "message";

const long duration = 10000;
long rememberTime=0;


#define DHTPIN D4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const long utcOffsetInSeconds = 3600;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void write(){
    File file = LittleFS.open("/data.csv", "w");
    file.close();
}

void append(){
    File file = LittleFS.open("/data.csv", "a");
    if(!file){
        Serial.println("Chyba otevření souboru");
        return;
    }
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    String value = "";
    Serial.println(t);
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    value = String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds()) + "," + String(t) + "," + String(h) + "\n";
    file.print(value);
    file.close();
}

void read(){
    File file = LittleFS.open("/data.csv", "r");
    while(file.available()){
        Serial.write(file.read());
    }
    Serial.println();
    file.close();
}
void dirs(){
    String str = "";
    Dir dir = LittleFS.openDir("/");
    while (dir.next()) {
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
    }
    Serial.print(str);
}

void setup() {

    Serial.begin(9600);
    dht.begin();
    timeClient.begin();
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, dns, gateway, subnet);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    if(!LittleFS.begin()){
        Serial.println("Failed to start File System");
        return;
    }
    dirs(); //files in ESP
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html"); //main page
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css"); //style
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/script.js", "text/javascript"); //script
    });
    server.on("/readADC", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/data.csv", "text/plain"); //file data
    });
    write();//creating file

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
    if( (millis()- rememberTime) >= duration){
        timeClient.update();  
    append();// adding new values
    read();// reading from file into console
    rememberTime=millis();// remember Current millis() time
    }
}