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
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //Version 1.1.2
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //Version 1.4.6

typedef struct
{
  float currentLimit;  
  bool restoreCmd;
}masterToNode_t;

typedef struct
{
  char id;
  bool overcurrentState;
}nodeToMaster_t;

const uint8_t chipEn = 15; 
const uint8_t chipSel = 2;
const byte roomTxPipe[][6] = {"rm1Tx","rm2Tx"};
const byte roomRxPipe[][6] = {"rm1Rx","rm1Rx"};
namespace Room
{
  const uint8_t numOfRooms = 2;
  const char* room1 = "room1";
  const char* room2 = "room2";  
};

RF24 nrf24(chipEn,chipSel);
LiquidCrystal_I2C lcd(0x27,20,4);
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Load Manager</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Room1: <input type="text" name="room1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Room2: <input type="text" name="room2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/restore1">
    <button type="submit">Restore room1</button>
  </form><br>
  <form action="/restore2">
    <button type="submit">Restore room2</button>
  </form>  
</body></html>)rawliteral";

void setup() 
{
  Serial.begin(115200);
  
  const char* ssid = "Load_Manager";
  const char* password = "Load_Manager";
  WiFi.softAP(ssid,password);
  IPAddress IP = WiFi.softAPIP();    
  Serial.print("IP address = ");
  Serial.println(IP);
  
  nrf24.begin();
  nrf24.setPALevel(RF24_PA_MAX);  
  nrf24.startListening();
  
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
  lcd.print("BOOTING.......");
  delay(1500);
  lcd.clear();
  
  //Menu
  lcd.print(">ROOM1:");
  lcd.setCursor(0,1);
  lcd.print(">ROOM2:");
  lcd.setCursor(0,2);
  lcd.print(">IP:");
  lcd.print(IP);
  
  static masterToNode_t masterToNode[Room::numOfRooms];
  //Send web page with input fields to client
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send_P(200,"text/html",index_html);
  });
  //Handle configuration of current limits from the user 
  server.on("/get",HTTP_GET,[](AsyncWebServerRequest *request) 
  {
    String inputMessage;
    String inputParam;
    if(request->hasParam(Room::room1)) 
    {
      inputMessage = request->getParam(Room::room1)->value();
      inputParam = Room::room1;
      nrf24.stopListening();
      nrf24.openWritingPipe(roomTxPipe[0]);
      masterToNode[0].currentLimit = inputMessage.toFloat();
      nrf24.write(&masterToNode[0],sizeof(masterToNode_t));
      nrf24.startListening();
    }
    else if(request->hasParam(Room::room2)) 
    {
      inputMessage = request->getParam(Room::room2)->value();
      inputParam = Room::room2;
      nrf24.stopListening();
      nrf24.openWritingPipe(roomTxPipe[1]);
      masterToNode[1].currentLimit = inputMessage.toFloat();
      nrf24.write(&masterToNode[1],sizeof(masterToNode_t));
      nrf24.startListening();
    }
    else 
    {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    request->send(200,"text/html","Current limit (A) for " 
                  + inputParam + " with value: " + inputMessage +
                  " has been sent to the system." +
                  "<br><a href=\"/\">Return to Home Page</a>");
  });
  //Handling the restoration of power to the rooms
  server.on("/restore1",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    nrf24.stopListening();
    nrf24.openWritingPipe(roomTxPipe[0]);
    masterToNode[0].restoreCmd = true;
    nrf24.write(&masterToNode[0],sizeof(masterToNode_t));
    masterToNode[0].restoreCmd = false; 
    nrf24.startListening();
    request->send_P(200,"text/html","Room1 restored <br><a href=\"/\">Return to Home Page</a>");
  });
  server.on("/restore2",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    nrf24.stopListening();
    nrf24.openWritingPipe(roomTxPipe[1]);
    masterToNode[1].restoreCmd = true;
    nrf24.write(&masterToNode[1],sizeof(masterToNode_t));
    masterToNode[1].restoreCmd = false; 
    nrf24.startListening();    
    request->send_P(200,"text/html","Room2 restored <br><a href=\"/\">Return to Home Page</a>");
  });
    
  server.begin();
}

void loop() 
{
  static nodeToMaster_t nodeToMaster[Room::numOfRooms];
  for(uint8_t i = 0; i < Room::numOfRooms; i++)
  {
    nrf24.openReadingPipe(1,roomRxPipe[i]);
    if(nrf24.available())
    {
      nrf24.read(&nodeToMaster[i],sizeof(nodeToMaster_t));
      Serial.print("node ID: ");
      Serial.println(nodeToMaster[i].id);
      Serial.print("node overcurrent state: ");
      Serial.println(nodeToMaster[i].overcurrentState);
    }
  }
}
