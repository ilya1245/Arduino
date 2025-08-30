#include "LedBlink.h"
#include "blink.h"

// #define RED_LED_PIN D2
// #define GREEN_LED_PIN D3
// #define BLUE_LED_PIN D4

Blinker blinkerOpen(BEEPER_PIN, 3000, 100, 100, 1, &Serial, SERIAL_SPEED);
// Blinker blinkerClose(BEEPER_PIN, 5000, 100, 100, 2, &Serial, SERIAL_SPEED);


// ---------------- Blink code ----------------
void disableAllBlinkers() {
  Serial.println("\ndisableAllBlinkers()");
  blinkerOpen.setActive(false);
  // blinkerClose.setActive(false);
}

void setBlinkParameters(Blinker &bl, byte numOfBlinks) {
  Serial.println("\nsetBlinkParameters()");
  disableAllBlinkers();
  bl.setNumOfBlinks(numOfBlinks);  
  bl.setActive(true);   
  bl.blink();
}

void blink() {
  Serial.println("\nblink()");
  blinkerOpen.blink();
  // blinkerClose.blink();
}