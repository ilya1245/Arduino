#include "processData.h"
#include "mqttClient.h"

DHT dht(DHTPIN, DHTTYPE);

void processSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // float h = 13.4f;
  // float t = 23.4f;

  if (!isnan(h) && !isnan(t)) {
    char tempStr[8], humStr[8];
    dtostrf(t, 4, 1, tempStr);
    dtostrf(h, 4, 1, humStr);
    mqttClient.publish(MQTT_TEMPERATURE_TOPIC, tempStr);
    mqttClient.publish(MQTT_HUMIDITY_TOPIC, humStr);
  }
}
