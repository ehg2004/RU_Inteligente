#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TTP229.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

//----------- RFID---------------//
#define SS_PIN 7
#define RST_PIN 6 
MFRC522 rfid(SS_PIN, RST_PIN); 
//-------------------------------//

//-------------------------DISPLAY--------------------------------//
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//----------------------------------------------------------------//

void setup() {
	Serial.begin(9600);
  SPI.begin(); 
  tft.begin();
  rfid.PCD_Init();  
}

void loop() {
  int x = 0, y = 0;
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  tft.setCursor(x, y);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);

  for(byte i = 0; i < rfid.uid.size; i++) 
    tft.println(rfid.uid.uidByte[i], HEX);

	delay(1000);
}