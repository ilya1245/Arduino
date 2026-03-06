#include "common.h"
#include "ir.h"

void setup() {
  mySerial.begin(SERIAL_SPEED);

  delay(1000);

  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(PLAYER_POWER_PIN, OUTPUT);
  digitalWrite(PLAYER_POWER_PIN, 0);

  keyPressTimer.setTimeout(KEY_PRESS_TIME);

  initIr();
}

void loop() {  
  processIr();    
}

