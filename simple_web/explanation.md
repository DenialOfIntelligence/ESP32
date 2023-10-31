# An explanation for the code in this dir

```
AsyncWebServer server(80);
```
Start the Web Server on port 80

```
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
```
This will handle requests on wrong uri's with this code `server.onNotFound(notFound);`

```
WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
}
```
Start the WIFI with `WiFi.begin(ssid, password);` and wait for connection.

```
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<a href=\"/on\">Turn the LED ON</a><a href=\"/off\">Turn the LED OFF</a>");
    });
```
`server.on` Defines an endpoint for a request (e.g /index.html) 

`request->send([..]"<button onclick=\"fetch('http://192.168.178.198/on')\">Turn LED ON</button>[..]");` on Request answer with 200 in the format text/html with this string

```
server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Was there ever anything here?");
        digitalWrite(LED_BUILTIN, HIGH);
    });
```
This is for when the user clicks on the ON button and fetches the /on url it turns the LED on!
