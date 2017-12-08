#include "Arduino.h"
#include <Sodaq_RN2483.h>
#include "Sodaq_Keys.h"
#define debugSerial SERIAL_PORT_MONITOR

#define loraSerial Serial2

uint8_t  i = 0;

//#define TEST

// ABP

#ifndef TEST
// Insert you own keys here! Edit the Sodaq_Keys.h file!
const uint8_t devAddr[4] = DEVADDR;
const uint8_t appSKey[16] = APPSKEY;
const uint8_t nwkSKey[16] = NWKSKEY;
#else
// Keys for testing!
const uint8_t devAddr[4] = {    \
  0x00, 0x00, 0x00, 0x00  };
const uint8_t appSKey[16] = {   \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00  };
const uint8_t nwkSKey[16] = {   \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00,       \
  0x00, 0x00, 0x00, 0x00 };
#endif //TEST

void setupLoRaABP(){  
  if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, false))
  {
    debugSerial.println("Communication to LoRaBEE successful.");
  }
  else
  {
    debugSerial.println("Communication to LoRaBEE failed!");
  }
}

void setup() {
  delay(3000);

  while ((!SerialUSB) && (millis() < 10000)){
    // Wait 10 seconds for the Serial Monitor
  }

  //Set baud rate
  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());

  // Debug output from LoRaBee
  LoRaBee.setDiag(debugSerial); // optional

  //connect to the LoRa Network
  setupLoRa();
}

void setupLoRa(){
  // ABP
  setupLoRaABP();
  /*
   * Set LoRaBee 
   */
  LoRaBee.setMacParam("dr ", "0"); // dr 0 --> SpreadingFactor 12
  LoRaBee.setMacParam("adr ", "on"); // adr on --> Sets if the adaptive data rate is to be enabled
  LoRaBee.setMacParam("pwridx ", "1"); // pwridx 1 == highest TXPower --> Sets the output power to be used on the next transmission
}

void sendPacket(String packet){
  switch (LoRaBee.send(1, (uint8_t*)packet.c_str(), packet.length()))
    {
    case NoError:
      debugSerial.println("Successful transmission.");
      break;
    case NoResponse:
      debugSerial.println("There was no response from the device.");
      setupLoRa();
      break;
    case Timeout:
      debugSerial.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
      delay(20000);
      break;
    case PayloadSizeError:
      debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
      break;
    case InternalError:
      debugSerial.println("Oh No! This shouldn't happen. Something is really wrong! Try restarting the device!\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case Busy:
      debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
      delay(10000);
      break;
    case NetworkFatalError:
      debugSerial.println("There is a non-recoverable error with the network connection. You should re-connect.\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case NotConnected:
      debugSerial.println("The device is not connected to the network. Please connect to the network before attempting to send data.\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case NoAcknowledgment:
      debugSerial.println("There was no acknowledgment sent back!");
      // When you this message you are probaly out of range of the network.
      break;
    default:
      break;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  String packet = "SODAQ ";
  packet[5] = i;
  sendPacket(packet);
  i++;
  delay(30000);
}

