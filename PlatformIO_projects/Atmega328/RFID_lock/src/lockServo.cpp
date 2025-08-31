#include "lockServo.h"

Servo lockServo;

int startPosition = 40;
int endPosition = 130;
boolean isLocked;

void lockBeep(int nums) {
  for (int i = 0; i < nums; i++) {
    digitalWrite(BEEPER_PIN, 1);
    digitalWrite(GREEN_LED_PIN, 1);
    delay(100); 
    digitalWrite(BEEPER_PIN, 0);
    digitalWrite(GREEN_LED_PIN, 0);
    delay(100);
  }
}

void moveFromStartToEnd() {
  for (int pos = startPosition; pos <= endPosition; pos++) {
    // Serial.print("pos = ");
    // Serial.println(pos);
    lockServo.write(pos);
    delay(10);  // задержка для плавного движения
  }
  delay(500);
  Serial.print("pos = ");
  Serial.println(endPosition);
  lockServo.write(endPosition - 5);
}

void moveFromEndToStart() {
  for (int pos = endPosition; pos >= startPosition; pos--) {
    lockServo.write(pos);
    // Serial.print("pos = ");
    // Serial.println(pos);
    delay(10);
  }
  delay(500);
  Serial.print("pos = ");
  Serial.println(startPosition);
  lockServo.write(startPosition + 5);
}

void closeLock() {
  Serial.println("\ncloseLock()");
  lockBeep(1);
  LOCK_POSITION == 0 ? moveFromStartToEnd() : moveFromEndToStart();
  isLocked = true;
}

void openLock() {
  Serial.println("\nopenLock()");
  lockBeep(2);
  LOCK_POSITION == 0 ? moveFromEndToStart() : moveFromStartToEnd();
  isLocked = false;
}
