#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LittleFS.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

#include "index.h"  //Web page header file

//defining temperature sensor
#define DHTPIN 4
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);


AsyncWebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "SSID";
const char* password = "PASSWORD";
// Set your Static IP address
IPAddress local_IP(10, 0, 1, 200);
// Set your Gateway
IPAddress gateway(10, 0, 1, 138);
// Set your Subnet Mask
IPAddress subnet(255, 255, 255, 0);




//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
 
 //reading temperature
/*void handleTemp() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 String value = String(t);

 
 server.send(200, "text/plane", value); //Send value only to client ajax request
}*/

void fileWriting(){
  File file = LittleFS.open("/file.txt", "w");
 
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
 
  int bytesWritten = file.print("TEST littlefs");
 
  if (bytesWritten > 0) {
    Serial.println("File was written");
    Serial.println(bytesWritten);
 
  } else {
    Serial.println("File write failed");
  }
 
  file.close();
}

void setup(void){
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  if(LittleFS.begin()){
    Serial.println("File system mounted with success");  
  }else{
    Serial.println("Error mounting the file system");
    return; 
  }

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
  Serial.println("STA Failed to configure");
  }

//ESP32 connects to your wifi -----------------------------------
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------

  fileWriting();

 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { //cesta pro root / webové stránky
    request->send(LittleFS, "/index.html", String(), false);
  });     //This is display page
  //server.on("/readADC", handleTemp);//To get update of value only
 
  dht.begin();
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop(void){
  //server.handleClient();
  //delay(1);
}