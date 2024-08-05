#include "store.h"
#include "common.h"
#include "tune.h"

int isOnAddress = 0;
int ledModeIrCommandAddress = 2;
int timeIntervalAddress = 4;
int pwmHighValueAddress = 8;
int pwmLowValueAddress = 12;




void writeSettings() {
  // if (isLedMode) {}
  EEPROM.write(isOnAddress, byte(isOn));
  printf("\nwrite isOn = %d", byte(isOn));  
  printf("\nwrite ledModeIrCommand = %d", ledModeIrCommand);
  if (ledModeIrCommand > 0) {
    EEPROM.write(ledModeIrCommandAddress, byte(ledModeIrCommand));
    printf("\nwrite ledModeIrCommand = %d", ledModeIrCommand);
  } 
  EEPROM.put(timeIntervalAddress, timeInterval);
  printf("\nwrite timeInterval = %d", timeInterval);
  EEPROM.put(pwmHighValueAddress, pwmHighValue);
  printf("\nwrite pwmHighValue = %d", pwmHighValue);
  EEPROM.put(pwmLowValueAddress, pwmLowValue);
  printf("\nwrite pwmLowValue = %d", pwmLowValue);
  printf("\n");

  EEPROM.commit();
}

void readSettings() {
  isOn = boolean(EEPROM.read(isOnAddress));
  printf("\nread isOn = %d", isOn);
  ledModeIrCommand = EEPROM.read(ledModeIrCommandAddress);  
  printf("\nread ledModeIrCommand = %d", ledModeIrCommand);
  EEPROM.get(timeIntervalAddress, timeInterval);
  printf("\nread timeInterval = %d", timeInterval);
  EEPROM.get(pwmHighValueAddress, pwmHighValue);
  printf("\nread pwmHighValue = %d", pwmHighValue);
  EEPROM.get(pwmLowValueAddress, pwmLowValue);
  printf("\nread pwmLowValue = %d", pwmLowValue);
  printf("\n");
}