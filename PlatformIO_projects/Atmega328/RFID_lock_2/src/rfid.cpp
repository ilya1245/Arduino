#include "rfid.h"

MFRC522 rfid(SS_PIN, RST_PIN);

const int allowedCount = sizeof(allowedCards) / sizeof(allowedCards[0]);

bool isCardAllowed(byte *uid, byte size) {
  if (size != 4) return false;  // мы проверяем только 4-байтовые UID

  for (int i = 0; i < allowedCount; i++) {
    bool match = true;
    for (int j = 0; j < 4; j++) {
      if (uid[j] != allowedCards[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}