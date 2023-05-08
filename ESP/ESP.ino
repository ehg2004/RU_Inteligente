#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

String serverName = "http://http://10.181.4.133:8888/index.php";

String SSId = "#";
String PASS = "12345678";

WiFiClient client;
HTTPClient http;

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}

void setup() {

  Serial.begin(74880);
  // Serial.setDebugOutput(true);
  WiFi.begin("#", "12345678");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    http.begin(client, serverPath.c_str());
    if(http.GET()>0)
    {
      Serial.println(http.getString());
    }
    else
    {
      Serial.println("EROOR");
    }
    http.end();
  }
}
