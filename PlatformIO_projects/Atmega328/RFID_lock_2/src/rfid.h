#include <SPI.h>
#include <MFRC522.h>
#include "common.h"

extern MFRC522 rfid;

const byte allowedCards[][4] = {
  {0xA9, 0x00, 0xC5, 0xB9}, //A9 00 C5 B9
  {0x63, 0x03, 0x72, 0x0C}, //63 03 72 0C
  {0x93, 0xC0, 0xA4, 0x0B} // 93 C0 A4 0B
};

extern bool isCardAllowed(byte *uid, byte size);