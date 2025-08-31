#include "common.h"
#include "rfid.h"
#include "lockServo.h"
#include "blink.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  disableAllBlinkers();
  SPI.begin();
  rfid.PCD_Init();

  lockServo.attach(SERVO_PIN);
  lockServo.write(startPosition);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT); 
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(GROUND_1_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(RED_LED_PIN, 0);
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(GROUND_1_PIN, 0);

  Serial.println("Поднесите карту...");

}

void showStatus(bool isLocked) {

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
    // digitalWrite(GREEN_LED_PIN, 1);
    if (isLocked) {
      openLock();
    } else {
      closeLock();
    }    
    // delay(1000);
    // digitalWrite(GREEN_LED_PIN, 0);
  } else {
    Serial.println("❌ Доступ запрещён");
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(BEEPER_PIN, 1);
    delay(1000);
    digitalWrite(RED_LED_PIN, 0);
    digitalWrite(BEEPER_PIN, 0);
  }

  rfid.PICC_HaltA();
}


