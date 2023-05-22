#pragma once

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

String lerRFID(MFRC522 *rfid)
{
  String str = String();
  if (!rfid->PICC_IsNewCardPresent()) return;
  if (!rfid->PICC_ReadCardSerial()) return;
  for(byte i = 0; i < rfid->uid.size; i++) 
  {
    str.concat(String(rfid->uid.uidByte[i], HEX));
  } 
  return str;
}
