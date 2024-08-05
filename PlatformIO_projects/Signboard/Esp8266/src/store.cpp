#include "store.h"
#include "common.h"

int isOnAddress = 0;
int ledModeIrCommandAddress = 2;


void writeSettings() {
  // if (isLedMode) {}
  EEPROM.write(isOnAddress, byte(isOn));
  printf("\nwrite isOn = %d", byte(isOn));  
  printf("\nledModeIrCommand = %d", ledModeIrCommand);
  if (ledModeIrCommand > 0) {
    EEPROM.write(ledModeIrCommandAddress, byte(ledModeIrCommand));
    printf("\nwrite ledModeIrCommand = %d", ledModeIrCommand);
  } 
  EEPROM.commit();
}

void readSettings() {
  isOn = boolean(EEPROM.read(isOnAddress));
  ledModeIrCommand = EEPROM.read(ledModeIrCommandAddress);
  printf("\nread isOn = %d", isOn);
  printf("\nread ledModeIrCommand = %d", ledModeIrCommand);
}