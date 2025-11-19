#include <WiFi.h>
#include "Adafruit_MQTT.h"

//Em "Library Manager", no Wokwi, pesquise por "Adafruit MQTT Library" e instale 
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "seu-usuário"
// No adafruit.io, crie uma conta gratuita e consiga suas credenciais. Troque abaixo pelas credenciais criadas.
#define AIO_KEY "sua-api-key"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish sensorFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensores");

void connectWiFi() {
  Serial.print("Conectando em ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}

void connectMQTT() {
  while (mqtt.connected() == false) {
    Serial.print("Conectando MQTT...");
    if (mqtt.connect()) {
      Serial.println("OK!");
    } else {
      Serial.print("falhou com erro ");
      Serial.println(mqtt.connectErrorString(mqtt.connect()));
      Serial.println("tentando de novo em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.processPackets(1000);

  float temperature = random(200, 350) / 10.0;
  float humidity = random(300, 850) / 10.0;
  float co  = random(0, 1000) / 10.0;   
  float co2 = random(400, 2000) / 1.0; 
  float ch4 = random(0, 5000) / 10.0;   
  float h2s = random(0, 100) / 1.0;     

  String payload = "{\"temperatura\":";
  payload += temperature;
  payload += ",\"umidade\":";
  payload += humidity;
  payload += ",\"co\":";
  payload += co;
  payload += ",\"co2\":";
  payload += co2;
  payload += ",\"ch4\":";
  payload += ch4;
  payload += ",\"h2s\":";
  payload += h2s;
  payload += "}";


  sensorFeed.publish(payload.c_str());

  Serial.print("Enviado JSON: ");
  Serial.println(payload);

  delay(5000);
}
