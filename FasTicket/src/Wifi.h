#pragma once

#include <Arduino.h>

void conectaWifi()
{
  /*
  const char* ssid = "#";
  const char* password = "12345678";
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  */
}

bool verificaSaldo(String rfid, int valor)
{
  /*
  conectaWifi();

  String serverName = "http://192.168.72.76:8888/";

  if(rfid && valor)
  {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;      

      String url = String("/arduino.php/?code=")+String(rfid)+String("&value=")+String(valor);

      http.begin(client, serverName+url);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        return bool(http.getString());
      } else {
        return 0;
      }
      http.end();
    } else {
      return 0;
    }
  }
  */
}