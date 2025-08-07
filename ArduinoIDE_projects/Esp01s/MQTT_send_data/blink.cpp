#include "blink.h"

Blinker blinkerWifiOk(WIFI_LED_PIN, 3000, 5, &Serial, SERIAL_SPEED);
Blinker blinkerWifiSearch(WIFI_LED_PIN, 1000, 500, &Serial, SERIAL_SPEED);

// ---------------- Blink code ----------------

void disableAllBlinkers() {
  blinkerWifiOk.setActive(false);
  blinkerWifiSearch.setActive(false);
}

void setBlinkParameters(Blinker &bl, byte numOfBlinks) {
  disableAllBlinkers();
  bl.setNumOfBlinks(numOfBlinks);  
  bl.setActive(true);   
  bl.blink();
}

void blink() {
//  Serial.println("\nFeeder: blink()");
  blinkerWifiOk.blink();
  blinkerWifiSearch.blink();
}