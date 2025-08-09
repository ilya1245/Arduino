#include <connection.h>
#include <blink.h>

// Попытка подключения к Wi-Fi
void tryConnect() {
  printf("Connecting to %s...\n", ssidStored.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidStored.c_str(), passStored.c_str());

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    printf("\nConnected to %s!\n", ssidStored.c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    apMode = false;
  } else {
    Serial.println("Failed to connect. Switching to AP mode.");
    startAPMode();
  }
}

void showWifiStatus() {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      if (Ping.ping(HOST_TO_PING, 1)) {
        setBlinkParameters(blinkerPingOk, 1);
        Serial.println("Интернет есть!");
      } else {
        setBlinkParameters(blinkerWifiConnected, 1);
        Serial.println("Интернета нет!");
      }
      break;
    // case WL_DISCONNECTED:
    //   setBlinkParameters(blinkerWifiDisconnected, 1);
    //   Serial.println("Сети нет!");
    default:
      setBlinkParameters(blinkerWifiDisconnected, 1);
      Serial.println("Сети нет!");
      break;
  }
}