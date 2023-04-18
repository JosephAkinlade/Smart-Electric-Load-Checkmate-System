#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //Version 1.4.6
#include <EEPROM.h>

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

const char nodeID = '2';
const uint8_t pzemTx = 4;
const uint8_t pzemRx = 5;
const uint8_t relayPin = 7;
const uint8_t chipEn = 9; 
const uint8_t chipSel = 10; 
const byte room2RxPipe[] = "rm2Tx";
const byte room2TxPipe[] = "rm2Rx";

SoftwareSerial pzemSerial(pzemTx,pzemRx);
PZEM004Tv30 pzem(pzemSerial);
RF24 nrf24(chipEn,chipSel);
uint32_t prevTime = 0;

/**
 * @brief Set float to zero if it is not a number.
*/
static void SetToZeroIfNaN(float* floatPtr)
{
  if(isnan(*floatPtr))
  {
    *floatPtr = 0.0;
  }
}

/**
 * @brief Send data to the master
*/
static void SendDataToMaster(RF24& nrf24,char id,bool overcurrentState)
{
  nodeToMaster_t nodeToMaster = {id,overcurrentState};
  nrf24.stopListening();
  nrf24.openWritingPipe(room2TxPipe);
  nrf24.write(&nodeToMaster,sizeof(nodeToMaster_t));
  nrf24.startListening();   
}

void setup() 
{
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  Serial.println("INIT");
  nrf24.begin();
  nrf24.openReadingPipe(1,room2RxPipe);
  nrf24.setPALevel(RF24_PA_MAX);
  nrf24.startListening();
  prevTime = millis();
}

void loop() 
{
  static masterToNode_t masterToNode;
  static bool overcurrentPrevDetected;
  static float currentLimitFromMem;
  static float measuredCurrent;

  if((millis() - prevTime) >= 500)
  {
    measuredCurrent = pzem.current();
    SetToZeroIfNaN(&measuredCurrent);
    prevTime = millis(); 
  }

  if(nrf24.available())
  {
    nrf24.read(&masterToNode,sizeof(masterToNode_t));
    SetToZeroIfNaN(&masterToNode.currentLimit);
    EEPROM.put(0,masterToNode.currentLimit);
    Serial.print("Current limit = ");
    Serial.println(masterToNode.currentLimit);
    Serial.print("Restore cmd = ");
    Serial.println(masterToNode.restoreCmd);
  }

  EEPROM.get(0,currentLimitFromMem);
  bool overcurrentDetected = lround(measuredCurrent * 100) > lround(currentLimitFromMem * 100);
  
  if(overcurrentDetected && !overcurrentPrevDetected)
  {
    Serial.println("Current limit exceeded");
    digitalWrite(relayPin,LOW); //disconnect the user from mains
    overcurrentPrevDetected = true; 
    SendDataToMaster(nrf24,nodeID,overcurrentPrevDetected);
  }
  
  if(!overcurrentDetected && masterToNode.restoreCmd)
  {
    Serial.println("Power restored");
    digitalWrite(relayPin,HIGH); //leave user connected to the mains 
    masterToNode.restoreCmd = false;
    overcurrentPrevDetected = false;
    SendDataToMaster(nrf24,nodeID,overcurrentPrevDetected);
  }
}
