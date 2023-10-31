//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//
#define LED_BUILTIN 2
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "*******";
const char* password = "********";

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<button onclick=\"fetch('http://192.168.178.198/on')\">Turn LED ON</button> <button onclick=\"fetch('http://192.168.178.198/off')\">Turn LED OFF</button>");
    });
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(LED_BUILTIN, HIGH);
        request->send(200, "text/plain", "Was there ever anything here?");
    });
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(LED_BUILTIN, LOW);
        request->send(200, "text/plain", "Was there ever anything here?");
    });
    
    server.onNotFound(notFound);


    server.begin();
}

void loop() {
}
