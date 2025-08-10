#include "blink.h"

Blinker blinkerPingOk(WIFI_LED_PIN, 3000, 20, &Serial, SERIAL_SPEED);
Blinker blinkerWifiConnected(WIFI_LED_PIN, 3000, 500, &Serial, SERIAL_SPEED);
Blinker blinkerWifiDisconnected(WIFI_LED_PIN, 1000, 500, &Serial, SERIAL_SPEED);

// ---------------- Blink code ----------------

void disableAllBlinkers() {
  blinkerPingOk.setActive(false);
  blinkerWifiConnected.setActive(false);
  blinkerWifiDisconnected.setActive(false);
}

void setBlinkParameters(Blinker &bl, byte numOfBlinks) {
  disableAllBlinkers();
  bl.setNumOfBlinks(numOfBlinks);  
  bl.setActive(true);   
  bl.blink();
}

void blink() {
  //  Serial.println("\nFeeder: blink()");
  blinkerPingOk.blink();
  blinkerWifiConnected.blink();
  blinkerWifiDisconnected.blink();
}