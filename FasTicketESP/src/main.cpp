#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TTP229.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Carrinho.h"
#include "Menu.h"
#include "teclado.h"
#include "RFID.h"
#include "Wifi.h"
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String dbg_msg;
ros::Publisher pub_dbg("RU_dbg_topic",&dbg_msg);
//----------- RFID---------------//
#define SS_PIN D8
#define RST_PIN 10
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

Carrinho car; // cart obj declaration

Menu menu; // menu obj declaration

void setup() {

  Serial.begin(57600); // starts Serial UART COMM // is used by rosserial node
  delay(1000);

 
  nh.initNode(); nh.advertise(pub_dbg); // starts ROS Nodes
  delay(1000);



  conectaWifi();// start WIFI

  SPI.begin(); //start SPI COMM

  tft.begin();// start display obj

  rfid.PCD_Init();  // start rfid_r obj

  menu.begin(&tft, &car); // start menu obj

  menu.imprimir(); // prints first menu page

  delay(1000);
}

void loop() {
  if(menu.getEstado() == EstINIC)
  {
    int key = 0;
    key = ler(ttp.ReadKey16());
    if(key < CONF && key > 0)
    {
      car.setItem(key);
      menu.atualizar(EstCARR);
    }
  }
  else if(menu.getEstado() == EstCARR)
  {
    int key = 0;
    key = ler(ttp.ReadKey16());
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
    int key = 0;
    key = ler(ttp.ReadKey16());
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
    
    String str = String();
    lerRFID(&rfid, &str);
    //Serial.println(str);
    if(str != String())
    { 
      //menu.atualizar(EstINIC);
      // Buscar no servidor se tem saldo
      int debitado = -1 ; //verificaSaldo(str, car.getValor());

      while( debitado < 0)
      {
        debitado = verificaSaldo(str, car.getValor()); 
        delayMicroseconds(100);
        yield();
        nh.spinOnce();
      }
      // Serial.println(debitado);  
      // if(debitado < 0)
      // {
      //   delay(500);
      //   return;
      // }
      // else if(debitado == 1)
      if(debitado == 1)
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
    menu.atualizar(EstINIC); //int_msg.data=
    int16_t* items = car.pub_items();
    int n = car.getNItems();
    char buf[n+1];
    buf[n]='\0';
    for(int i = 0; i < n ; i++)
    {
      buf[i] = (char)(items[i]+'0');//convert int to numerical char//itoa(items[i],&buf[i],10);//for bigger numbers, could be used  
    }

    dbg_msg.data=buf;
    pub_dbg.publish(&dbg_msg);
    dbg_msg.data = NULL;
    free(items); 
    items = NULL;
    car.reset();
    delay(5000);
  }
  nh.spinOnce();
  //delay(1000);
  menu.imprimir();

}