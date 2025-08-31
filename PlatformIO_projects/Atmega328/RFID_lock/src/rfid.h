#include <SPI.h>
#include <MFRC522.h>
#include "common.h"

extern MFRC522 rfid;

const byte allowedCards[][4] = {
  {0xA9, 0x00, 0xC5, 0xB9}, //A9 00 C5 B9
  {0x1A, 0x52, 0x48, 0x7F}, //1A 52 48 7F
  {0x93, 0xC0, 0xA4, 0x0B}, // 93 C0 A4 0B
  {0xAC, 0xDD, 0xF5, 0x16} // AC DD F5 16
};

extern bool isCardAllowed(byte *uid, byte size);