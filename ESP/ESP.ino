#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "#";
const char* password = "12345678";
String serverName = "http://192.168.72.76:8888/";
String uid_buf = String();
String value_buf = String();

void getRFID()
{
  if (Serial.available() > 0) 
  { 
      uid_buf = Serial.readString();
  }
}

void getValor()
{
  if (Serial.available() > 0) 
  { 
      value_buf = Serial.readString();
  }
}

void VerificaSaldo(String RFID,String valor)
{
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;      

    String url = String("/arduino.php/?code=")+String(RFID)+String("&value=")+String(valor);

    http.begin(client, serverName+url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      /*----------MUDAR TALVEZ-------------------*/
      Serial.println(http.getString());
      /*-----------------------------------------*/
    } else {
      Serial.println(-1);
    }

    http.end();

  } else {
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if(uid_buf == String()){
    getRFID();
  }else if(value_buf == String()){
    getValor();
  }else{
    VerificaSaldo(uid_buf, value_buf);
    uid_buf= String();
    value_buf= String();
  }
  delay(500);
}
