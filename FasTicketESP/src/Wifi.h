#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void conectaWifi()
{
  const char* ssid = "#";
  const char* password = "12345678";
  WiFi.begin(ssid, password);
}

int verificaSaldo(String rfid, int valor)
{
  
  String serverName = "http://192.168.72.76:8888/";

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;      

    String url = String("/arduino.php/?code=")+String(rfid)+String("&value=")+String(valor);
    Serial.print(url);

    http.begin(client, serverName+url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      return bool(http.getString());
    } else {
      return -1;
    }
    http.end();
  } else { 
    return -2;
  }
}