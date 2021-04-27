#include "DueCANLayer.h"

// CAN Layer functions
extern byte canInit(byte cPort, long lBaudRate);
extern byte canTx(byte cPort, long lMsgID, bool bExtendedFormat, byte* cData, byte cDataLen);
extern byte canRx(byte cPort, long* lMsgID, bool* bExtendedFormat, byte* cData, byte* cDataLen);

// Declare pins

void setup()
{
  // Set the serial interface baud rate
  Serial.begin(115200);
  Serial.print("Setup\n");

  // Initialize both CAN controllers
  if(canInit(0, CAN_BPS_250K) == CAN_OK)
  {
    Serial.print("CAN0: Initialized Successfully.\n\r");
  }
  else
  {
    Serial.print("CAN0: Initialization Failed.\n\r");
  }
}// end setup

void loop()
{
  while(1)  // Endless loop
  {
    delay(100);
    byte rxData[8];
    byte len;
    long msgId;
    bool extended;
    byte errorData1[8];// = {0, 0, 0, 0, 0x04, 0x0f, 0x64, 0}; // (0, 0, 0, 0, 4, 15, 100, 0)
    byte errorData2[] = {0, 0, 0, 0, 0x14, 0x10, 0, 0}; // (0, 0, 0, 0, 20, 16, 0, 0)
    byte errorData3[] = {0x98, 0x58, 0, 0xA0, 0x28, 0, 0, 0}; // (152, 88, 0, 160, 40, 0, 0, 0)
    for(int i = 4; i < 8; i++)
    {
      errorData1[i] = random(0, 0x64);
    }
    errorData1[4] = random (3, 5);

//  byte errorData4[] =

// Sending the BMS Error Data as CAN messages
// Arduino will act as a BMS by sendings these data
    if(canTx(0, 0x6B0, false, errorData1, 8) == CAN_OK)
    {
      Serial.print("Sent CAN Frame\n");
    }
    else
    {
      Serial.print("Failed to Send CAN Frame\n");
    }
    if(canTx(0, 0x6B1, false, errorData2, 8) == CAN_OK)
    {
      Serial.print("Sent CAN Frame\n");
    }
    else
    {
      Serial.print("Failed to Send CAN Frame\n");
    }
    if(canTx(0, 0x6B2, false, errorData3, 8) == CAN_OK)
    {
      Serial.print("Sent CAN Frame\n");
    }
    else
    {
      Serial.print("Failed to Send CAN Frame\n");
    }
    /*if(canTx(0, 0x600, false, errorData4, 8) == CAN_OK)
    {
      Serial.print("Sent CAN Frame\n");
    }
    else
    {
      Serial.print("Failed to Send CAN Frame\n");
    }
*/  
  }// end while
}// end loop
