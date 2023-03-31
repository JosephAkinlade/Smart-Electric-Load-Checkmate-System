//ESP8266 V2.5.2 

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //Version 1.1.2
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //Version 1.4.6

const uint8_t chipEn = 15;
const uint8_t chipSel = 5;
const byte addr1[][6] = {"01310","10040"};
const byte addr2[][6] = {"05210","13120"};
RF24 nrf24(chipEn,chipSel);
LiquidCrystal_I2C lcd(0x27,20,4);
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
  
  const char* ssid = "Load_Manager";
  const char* password = "Load_Manager";
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();    
  
  //Startup message
  lcd.init();
  lcd.backlight();
  lcd.print("SMART LOAD MANAGER");
  lcd.setCursor(0,1);
  for(uint8_t i = 0; i < 20; i++)
  {
    lcd.print('*');
  }
  delay(1500);
  lcd.setCursor(0,2);
  lcd.print("STATUS: ");
  lcd.setCursor(0,3);
  lcd.print("INITIALIZING...");
  delay(1500);
  lcd.clear();

  lcd.setCursor(0,3);
  lcd.print(">IP:");
  lcd.print(IP);
  
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
