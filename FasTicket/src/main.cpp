#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TTP229.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Carrinho.h"
#include "Menu.h"
#include "teclado.h"

//----------- RFID---------------//
#define SS_PIN 6
#define RST_PIN 7
MFRC522 rfid(SS_PIN, RST_PIN); 
//-------------------------------//

//-------------------------DISPLAY--------------------------------//
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
//----------------------------------------------------------------//

//-------------------------TECLADO--------------------------------//
#define SCL_PIN 2
#define SDO_PIN 3
TTP229 ttp(SCL_PIN, SDO_PIN);
//----------------------------------------------------------------//

Carrinho car;
Menu menu;

void setup() {
	Serial.begin(115200);
  SPI.begin(); 
  tft.begin();
  rfid.PCD_Init();  
  menu.begin(&tft, &car);
}

void loop() {
  Serial.println("AAAAA");
  
  if(ttp.GetKey16() == RESET)
  {
    car.reset();
    menu.atualizar(EstINIC);
  }
  if(menu.getEstado() == EstINIC)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF)
    {
      car.setItem(key);
      menu.atualizar(EstCARR);
    }
  }
  else if(menu.getEstado() == EstCARR)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF)
    {
      car.setItem(key);
      menu.atualizar(EstCARR);
    }
    else if(key == CONF)
    {
      menu.atualizar(EstRFID);
    }
    else if(key == CANC)
    {
      menu.atualizar(EstCANC);
    }
  }
  else if (menu.getEstado() == EstCANC)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF)
    {
      car.deleteItem(key);
      menu.atualizar(EstCARR);
    }
  }
  else if(menu.getEstado() == EstRFID)
  {
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial()) return;
    // Buscar no servidor se tem saldo
    int debitado;
    if(debitado)
    {
      menu.atualizar(EstPGMT);
    }
    else
    {
      menu.atualizar(EstSSAL);
    }
  }
  else if (menu.getEstado() == EstSSAL)
  {
    delay(5000);
    car.reset();
    menu.atualizar(EstINIC);
  }
  else if(menu.getEstado() == EstPGMT)
  {
    // imprimir 
    menu.atualizar(EstINIC);
    car.reset();
    delay(5000);
  }
  menu.imprimir();
  
}

/*
for(byte i = 0; i < rfid.uid.size; i++) {
  tft.print(rfid.uid.uidByte[i], HEX);
  Serial.println(rfid.uid.uidByte[i], HEX);
}
*/