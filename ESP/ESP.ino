#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Enzo";
const char* password = "#Enzo04$";
const char* serverName = "http://127.0.0.1:8000"; // URL do servidor a ser requisitado

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Conectando-se à rede Wi-Fi ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado à rede Wi-Fi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    Serial.print("Enviando requisição para ");
    Serial.println(serverName);

    http.begin(client, serverName);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Resposta do servidor: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Não foi possível se conectar à rede Wi-Fi");
  }

  delay(500); // Espere 5 segundos antes de enviar a próxima requisição
}