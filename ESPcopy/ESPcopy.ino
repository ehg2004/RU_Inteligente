#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "#";
const char* password = "12345678";
String serverName = "http://192.168.91.76:8888/"; // servidor a ser requisitado

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  //Serial.print("Conectando-se à rede Wi-Fi ");
  //Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Serial.println("Conectado à rede Wi-Fi");
}

void loop() {

  int RFID = 123;
  int valor = 5;

  if(RFID && valor)
  {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;      

      //Serial.print("Enviando requisição para ");
      String url = String("/arduino.php/?code=")+String(RFID)+String("&value=")+String(valor);
      //Serial.println(serverName);

      http.begin(client, serverName+url);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        //Serial.print("Resposta do servidor: ");
        //Serial.println(httpResponseCode);
        Serial.println(http.getString());
      } else {
        Serial.println(-1);
      }
      http.end();
    } else {
      Serial.println(-2);
      //Serial.println("Não foi possível se conectar à rede Wi-Fi");
    }
  }
  delay(500); // Espere 5 segundos antes de enviar a próxima requisição
}