#include "mqttClient.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectClientIfNeeded() {
  if (isPingOk) {
    while (!mqttClient.connected()) {
      Serial.println("connectClientIfNeeded() - reconnect");
      // mqttClient.connect(MQTT_CLIENT_ID);
      if (mqttClient.connect(MQTT_CLIENT_ID)) {
        Serial.println("connectClientIfNeeded() - connected");
        mqttClient.subscribe(MQTT_TEMPERATURE_CORRECTION_COMMAND_TOPIC);
      } else {
        delay(5000);
      }
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  printf("\ncallback() - %s\n", String(topic));
  // Serial.println("callback() - String(topic)");
  payload[length] = '\0';  // превращаем в строку
  String message = String((char*)payload);
  printf("callback() - %s\n", message);
  
  if (String(topic) == MQTT_TEMPERATURE_CORRECTION_COMMAND_TOPIC) {
    Serial.println("callback() - condition is true ");
    temperatureCorrection = message.toFloat();
  }
}

