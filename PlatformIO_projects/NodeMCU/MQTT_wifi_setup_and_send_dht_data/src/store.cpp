#include "common.h"
#include "store.h"
#include "accessPoint.h"

// Чтение сохранённых данных
void loadCredentials() {
  if (EEPROM.read(EEPROM_FLAG_ADDR) == 'C') {
    byte ssidLen = EEPROM.read(EEPROM_SSID_LEN_ADDR);
    byte passLen = EEPROM.read(EEPROM_PASS_LEN_ADDR);

    char ssidBuf[ssidLen + 1];
    char passBuf[passLen + 1];

    for (byte i = 0; i < ssidLen; i++) {
      ssidBuf[i] = EEPROM.read(EEPROM_DATA_ADDR + i);
    }
    ssidBuf[ssidLen] = '\0';

    for (byte i = 0; i < passLen; i++) {
      passBuf[i] = EEPROM.read(EEPROM_DATA_ADDR + ssidLen + i);
    }
    passBuf[passLen] = '\0';

    ssidStored = String(ssidBuf);
    passStored = String(passBuf);

    Serial.println("Loaded from EEPROM:");
    Serial.println("SSID: " + ssidStored);
    Serial.println("PASS: " + passStored);
  } else {
    ssidStored = "";
    passStored = "";
    Serial.println("No credentials in EEPROM.");
  }
}

// Сохранение данных
void saveCredentials(const String &ssid, const String &pass) {
  EEPROM.write(EEPROM_FLAG_ADDR, 'C');
  EEPROM.write(EEPROM_SSID_LEN_ADDR, ssid.length());
  EEPROM.write(EEPROM_PASS_LEN_ADDR, pass.length());

  for (byte i = 0; i < ssid.length(); i++) {
    EEPROM.write(EEPROM_DATA_ADDR + i, ssid[i]);
  }

  for (byte i = 0; i < pass.length(); i++) {
    EEPROM.write(EEPROM_DATA_ADDR + ssid.length() + i, pass[i]);
  }

  EEPROM.commit();
}

