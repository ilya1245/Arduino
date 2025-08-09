#include "common.h"
#include "blink.h"
#include "connection.h"
#include "accessPoint.h"
#include "store.h"


void setup() {
  Serial.begin(SERIAL_SPEED);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(WIFI_LED_PIN, OUTPUT);
  digitalWrite(WIFI_LED_PIN, HIGH);

  blinkerPingOk.setInvertBlinking(true);
  blinkerWifiConnected.setInvertBlinking(true);
  blinkerWifiDisconnected.setInvertBlinking(true);

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
    server.handleClient();
  } else {
    // Мы в режиме клиента — выполняем основную работу
    static unsigned long lastBlink = 0;
    static bool ledState = false;

    if (timer_5s.isReady()) {
      printf("\nWiFi.status() is %d\n", WiFi.status());
      showWifiStatus();
    }
    blink();
  }  
}
