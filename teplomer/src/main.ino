#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "index.h"  //Web page header file

//defining temperature sensor
#define DHTPIN 4
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);


ESP8266WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "YOUR-SSID-HERE";
const char* password = "YOUR-PASSWORD-HERE";

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
 //reading temperature
void handleTemp() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 String value = String(t);

 
 server.send(200, "text/plane", value); //Send value only to client ajax request
}

void setup(void){
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");

//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connect to your wifi
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
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", handleTemp);//To get update of value only
 
  dht.begin();
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  delay(1);
}