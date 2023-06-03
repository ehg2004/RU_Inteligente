#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

 #include "Credentials.h"
/*

create another file to save your wifi credentials

// ----- Credentials.h ----- //
// #ifndef CREDENTIALS
// #define CREDENTIALS
// #define SSID yourssid
// #define PSSWD yourpsswd
// #define MY_IP yourip
// #endif


*/

void conectaWifi()
{
  #ifdef WIFI_BYPASS // define this in main .cpp to test without wifi
   return ;
  #endif

  #ifndef CREDENTIALS
  const char* ssid = "#";
  const char* password = "12345678";
  #else
  const char* ssid = SSID;
  const char* password = PSSWD;
  #endif

  WiFi.begin(ssid, password);

}

int verificaSaldo(String rfid, int valor)
{

  #ifdef WIFI_BYPASS // define this in main .cpp to test without wifi
  return 1;
  #endif
  #ifndef CREDENTIALS
  String serverName = String(F("http://"))+ String(F("192.168.72.76")) + String(F(":8888/")); 
  #else
  String serverName = String(F("http://")) + String(F(MY_IP))  +String(F(":8888/")); 
  #endif

  while (WiFi.status() != WL_CONNECTED)
  {
    // Serial.print(".");
    yield();
    delayMicroseconds(10);
  }

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;      

    String url = String(F("/arduino.php/?code="))+String(rfid)+String(F("&value="))+String(valor);

    http.begin(client, serverName+url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String a = http.getString();
      if(a == "0")
      {
        return 0;
      }
      return bool(a);
    } 
    else {
      return -1;
    }
    http.end();
  } else { 
    return -2;
  }
}