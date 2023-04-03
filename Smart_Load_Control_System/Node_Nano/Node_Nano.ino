#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
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

const char nodeID = '1';
const uint8_t pzemTx = 4;
const uint8_t pzemRx = 5;
const uint8_t relayPin = 7;
const uint8_t chipEn = 9; 
const uint8_t chipSel = 10; 
const byte room1RxPipe[] = "rm1Tx";
const byte room1TxPipe[] = "rm1Rx";

SoftwareSerial pzemSerial(pzemTx,pzemRx);
PZEM004Tv30 pzem(pzemSerial);
RF24 nrf24(chipEn,chipSel);
uint32_t prevTime = millis();
static masterToNode_t masterToNode;

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
  nrf24.openWritingPipe(room1TxPipe);
  nrf24.write(&nodeToMaster,sizeof(nodeToMaster_t));
  nrf24.startListening();   
}

void setup() 
{
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  Serial.println("INIT");
  nrf24.begin();
  nrf24.openReadingPipe(1,room1RxPipe);
  nrf24.setPALevel(RF24_PA_MAX);
  nrf24.startListening();
}

void loop() 
{
  static bool overcurrentPrevDetected;
  //float measuredCurrent = pzem.current();
  float measuredCurrent = 10.2;
  SetToZeroIfNaN(&measuredCurrent);

  if(nrf24.available())
  {
    nrf24.read(&masterToNode,sizeof(masterToNode_t));
    Serial.print("Current limit = ");
    Serial.println(masterToNode.currentLimit);
    Serial.print("Restore cmd = ");
    Serial.println(masterToNode.restoreCmd);
  }
  
  bool overcurrentDetected = lround(measuredCurrent * 100) > lround(masterToNode.currentLimit * 100);
  
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
