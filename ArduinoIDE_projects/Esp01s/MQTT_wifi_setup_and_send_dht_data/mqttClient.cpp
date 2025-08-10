#include "mqttClient.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectClientIfNeeded() {
  if (isPingOk) {
    while (!mqttClient.connected()) {
      Serial.println("connectClientIfNeeded() - reconnect");
      mqttClient.connect(MQTT_CLIENT_ID);
    }
  }
}

