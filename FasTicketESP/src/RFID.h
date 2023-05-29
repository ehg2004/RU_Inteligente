#pragma once

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

void lerRFID(MFRC522 *rfid, String *str)
{
  if (!rfid->PICC_IsNewCardPresent()) return;
  if (!rfid->PICC_ReadCardSerial()) return;
  for(int i = 0; i < rfid->uid.size; i++) 
  {
    str->concat(String(rfid->uid.uidByte[i], HEX));
  } 
}
