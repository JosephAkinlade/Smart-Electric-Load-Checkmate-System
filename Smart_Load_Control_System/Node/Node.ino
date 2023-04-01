#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //Version 1.4.6

typedef struct
{
  float currentLimit;
  bool restoreCmd;
}masterToNode_t;

const uint8_t chipEn = 8; 
const uint8_t chipSel = 9; 
const byte room1RxPipe[] = "rm1Tx";
const byte room1TxPipe[] = "rm1Rx";
const uint8_t relayPin = 5;

RF24 nrf24(chipEn,chipSel);

uint32_t t = millis();

void setup() 
{
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  pinMode(relayPin,HIGH);
  nrf24.begin();
  nrf24.openReadingPipe(1,room1RxPipe);
  nrf24.setPALevel(RF24_PA_MAX);
  nrf24.startListening();
}

void loop() 
{
  static masterToNode_t masterToNode;
  /*
   * If current > limit : pinMode(relayPin,LOW)
  */
  if((millis() - t) >= 1500)
  {
    nrf24.stopListening();
    nrf24.openWritingPipe(room1TxPipe);
    char c = 'c';
    nrf24.write(&c,sizeof(c));
    nrf24.startListening();
    t = millis();
  }
  
  if(nrf24.available())
  {
    nrf24.read(&masterToNode,sizeof(masterToNode));
    Serial.print("Current limit = ");
    Serial.println(masterToNode.currentLimit,2);

    if(masterToNode.restoreCmd)
    {
      Serial.println("Power restored");
      digitalWrite(relayPin,HIGH);
    }
  }
}
