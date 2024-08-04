#include "LedBlink.h"
#include "blink.h"

#define RED_LED_PIN D2
#define GREEN_LED_PIN D3
#define BLUE_LED_PIN D4

Blinker blinker_r(RED_LED_PIN, 3000, 100, 100, 1, &Serial, SERIAL_SPEED);
Blinker blinker_g(GREEN_LED_PIN, 3000, 100, 100, 1, &Serial, SERIAL_SPEED);
Blinker blinker_b(BLUE_LED_PIN, 3000, 10, 200, 1, &Serial, SERIAL_SPEED);

// ---------------- Blink code ----------------
void disableAllBlinkers() {
  blinker_r.setActive(false);
  blinker_g.setActive(false);
  blinker_b.setActive(false);
}

void setBlinkParameters(Blinker &bl, byte numOfBlinks) {
  disableAllBlinkers();
  bl.setNumOfBlinks(numOfBlinks);  
  bl.setActive(true);   
  bl.blink();
}

void blink() {
//  Serial.println("\nblink()");
  blinker_r.blink();
  blinker_g.blink();
  blinker_b.blink();
}