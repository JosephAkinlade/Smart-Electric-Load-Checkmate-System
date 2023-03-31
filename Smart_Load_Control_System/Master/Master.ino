//ESP8266 V2.5.2 

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

namespace Room
{
  const char* room1 = "room1";
  const char* room2 = "room2";  
};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    room1: <input type="text" name="room1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    room2: <input type="text" name="room2">
    <input type="submit" value="Submit">
  </form><br>
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) 
{
  request->send(404,"text/plain","Not found");
}

void setup() 
{
  Serial.begin(115200);
  Serial.print("Setting AP (Access Point)…");
  const char* ssid = "Load_Manager";
  const char* password = "Load_Manager";
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // Send web page with input fields to client
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send_P(200,"text/html",index_html);
  });

  server.on("/get",HTTP_GET,[](AsyncWebServerRequest *request) 
  {
    String inputMessage;
    String inputParam;
    if(request->hasParam(Room::room1)) 
    {
      inputMessage = request->getParam(Room::room1)->value();
      inputParam = Room::room1;
    }
    else if(request->hasParam(Room::room2)) 
    {
      inputMessage = request->getParam(Room::room2)->value();
      inputParam = Room::room2;
    }
    else 
    {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200,"text/html","Current limit (A) for " 
                  + inputParam + " with value: " + inputMessage +
                  " has been sent to the system." +
                  "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() 
{  
}
