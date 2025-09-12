#include "common.h"
#include "rfid.h"
#include "lockServo.h"
#include "store.h"

void keepLockPosition() {
  boolean positionFlag = isLocked;
  LOCK_POSITION == 0 ? positionFlag = isLocked : positionFlag = !isLocked;
  if (positionFlag) {
    lockServo.write(endPosition);
    delay(500);
    lockServo.write(endPosition - 5);
  } else {
    lockServo.write(startPosition);
    delay(500);
    lockServo.write(startPosition + 5);
  }
}

void setup() {
  Serial.begin(SERIAL_SPEED);
  SPI.begin();
  rfid.PCD_Init();

  // writeDefaultSettings();
  readSettings();
  
  lockServo.attach(SERVO_PIN);
  keepLockPosition();
  
  // pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT); 
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(GROUND_1_PIN, OUTPUT);
  // digitalWrite(RELAY_PIN, 0);
  digitalWrite(RED_LED_PIN, 0);
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(GROUND_1_PIN, 0);

  Serial.println("Поднесите карту...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (isCardAllowed(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("✅ Доступ разрешён");
    isLocked ? openLock() : closeLock();  
    writeSettings();
  } else {
    Serial.println("❌ Доступ запрещён");
    digitalWrite(RED_LED_PIN, 1);
    // digitalWrite(BEEPER_PIN, 1);
    tone(BEEPER_PIN, 2000);
    delay(1000);
    digitalWrite(RED_LED_PIN, 0);
    // digitalWrite(BEEPER_PIN, 0);
    noTone(BEEPER_PIN);
  }

  rfid.PICC_HaltA();
}


