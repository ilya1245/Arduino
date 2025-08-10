#include "common.h"
#include "blink.h"
#include "connection.h"
#include "accessPoint.h"
#include "store.h"
#include "mqttClient.h"
#include "processData.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(WIFI_LED_PIN, OUTPUT);
  digitalWrite(WIFI_LED_PIN, HIGH);

  // blinkerPingOk.setInvertBlinking(true);
  // blinkerWifiConnected.setInvertBlinking(true);
  // blinkerWifiDisconnected.setInvertBlinking(true);

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

  loadCredentials();

  if (ssidStored.length() > 0) {
    tryConnect();
    if (WiFi.status() != WL_CONNECTED) {
      startAPMode();
    }
  } else {
    startAPMode();
  }
}

void loop() {
  if (apMode) {
    // Мы в режиме точки доступа — обрабатываем запросы
    apServer.handleClient();
  } else {
    if (timer_10s.isReady()) {
      printf("\nWiFi.status() is %d\n", WiFi.status());
      showWifiStatus();
      connectClientIfNeeded();
      processSensorData();
      mqttClient.loop();      
    }
    blink();
  }  
}
