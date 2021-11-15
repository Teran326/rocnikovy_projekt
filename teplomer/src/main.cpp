#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <AsyncJson.h>
#include <SPIFFS.h>

// Replace with your network credentials
const char* ssid     = "AndroidAP_8064";
const char* password = "something";

// Set web server port number to 80
WiFiServer server(80);

// Auxiliar variables to store the current output state
String output17State = "off";

// Assign output variables to GPIO pins
const int output17 = 4;

void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  pinMode(output17, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output17, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  server.addHandler(new AsyncCallbackJsonWebHandler("/led", [](AsyncWebServerRequest *request, JsonVariant &json) {
    const JsonObject &jsonObj = json.as<JsonObject>();
    if (jsonObj["on"])
    {
      Serial.println("Turn on LED");
      digitalWrite(BUILTIN_LED, HIGH);
    }
    else
    {
      Serial.println("Turn off LED");
      digitalWrite(BUILTIN_LED, LOW);
    }
    request->send(200, "OK");
  }));

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.onNotFound([](AsyncWebServerRequest *request) {
    if (request->method() == HTTP_OPTIONS)
    {
      request->send(200);
    }
    else
    {
      Serial.println("Not found");
      request->send(404, "Not found");
    }
  });

  server.begin();
}

void loop(){
}