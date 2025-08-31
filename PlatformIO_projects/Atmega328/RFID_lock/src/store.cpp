#include "store.h"

void writeSettings() {
  EEPROM.write(LOCK_STATUS_ADDRESS, byte(isLocked));
  printf("\nwrite isLocked = %d\n", byte(isLocked)); 
}

void writeDefaultSettings() {
  isLocked = 0;
  EEPROM.write(LOCK_STATUS_ADDRESS, byte(isLocked));
  printf("\nwrite isLocked = %d\n", byte(isLocked));
}

void readSettings() {
  isLocked = boolean(EEPROM.read(LOCK_STATUS_ADDRESS));
  printf("\nread isLocked = %d\n", isLocked);
}