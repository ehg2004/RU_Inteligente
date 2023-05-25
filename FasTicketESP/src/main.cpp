#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TTP229.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Carrinho.h"
#include "Menu.h"
#include "teclado.h"
//#include "RFID.h"
//#include "Wifi.h"

//----------- RFID---------------//
#define SS_PIN 6
#define RST_PIN 7
MFRC522 rfid(SS_PIN, RST_PIN); 
//-------------------------------//

//-------------------------DISPLAY--------------------------------//
#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
//----------------------------------------------------------------//

//-------------------------TECLADO--------------------------------//
#define SCL_PIN D1
#define SDO_PIN D0
TTP229 ttp(SCL_PIN, SDO_PIN);
//----------------------------------------------------------------//

Carrinho car;
Menu menu;

void setup() {
	Serial.begin(115200);
  SPI.begin(); 
  tft.begin();
  //rfid.PCD_Init();  
  menu.begin(&tft, &car);
  menu.imprimir();
}

void loop() {
  if(menu.getEstado() == EstINIC)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF && key > 0)
    {
      car.setItem(key);
      menu.atualizar(EstCARR);
    }
  }
  else if(menu.getEstado() == EstCARR)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF && key > 0)
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
    else if(key == RESET)
    {
      car.reset();
      menu.atualizar(EstINIC);
    }
  }
  else if (menu.getEstado() == EstCANC)
  {
    int key = ler(ttp.ReadKey16());
    if(key < CONF && key > 0)
    {
      car.deleteItem(key-1);
      menu.atualizar(EstCARR);
    }
    else if(key == RESET)
    {
      car.reset();
      menu.atualizar(EstINIC);
    }
  }
  else if(menu.getEstado() == EstRFID)
  {
    if(ttp.GetKey16() == RESET)
    {
      car.reset();
      menu.atualizar(EstINIC);
    }
    
    //String str = lerRFID(&rfid);
    String str = String();
    if(str != String())
    {
      
      // Buscar no servidor se tem saldo
      //bool debitado = verificaSaldo(str, car.getValor());
      bool debitado = 0;
      if(debitado)
      {
        menu.atualizar(EstPGMT);
      }
      else
      {
        menu.atualizar(EstSSAL);
      }
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