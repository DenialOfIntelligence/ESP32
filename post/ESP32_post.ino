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

const char* ssid = "********";
const char* password = "*********";

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

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/LED", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }

        if (message == "ON"){
          digitalWrite(LED_BUILTIN, HIGH);
          request->send(200, "text/plain", "OK \n");
        } else if (message == "OFF") {
          digitalWrite(LED_BUILTIN, LOW);
          request->send(200, "text/plain", "OK \n");
        }else {
          request->send(400, "text/plain", "Bad Request\n");
        }
        
        
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
}
