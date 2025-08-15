#include "store.h"
#include "common.h"
#include "tune.h"
#include "action.h"
#include "bt.h"

int isOnAddress = 0;
int modeAddress = 2;
int timeIntervalAddress = 4;
int pwmHighValueAddress = 8;
int pwmLowValueAddress = 12;

void writeSettings() {  
  printf("\nwrite isOn = %d", byte(isOn)); 
  EEPROM.write(isOnAddress, byte(isOn)); 
  printf("\nwrite mode = %d", mode);
  EEPROM.write(modeAddress, byte(mode)); 
  EEPROM.put(timeIntervalAddress, timeInterval);
  printf("\nwrite timeInterval = %d", timeInterval);
  EEPROM.put(pwmHighValueAddress, pwmHighValue);
  printf("\nwrite pwmHighValue = %d", pwmHighValue);
  EEPROM.put(pwmLowValueAddress, pwmLowValue);
  printf("\nwrite pwmLowValue = %d", pwmLowValue);
  printf("\n");

  EEPROM.commit();
}

void writeDefaultSettings() {
  EEPROM.write(isOnAddress, 0);
  printf("\nwrite isOn = %d", 0);
  EEPROM.write(mode, 0);
  printf("\nwrite mode = %d", 0);
  EEPROM.put(timeIntervalAddress, 500);
  printf("\nwrite timeInterval = %d", 500);
  EEPROM.put(pwmHighValueAddress, 200);
  printf("\nwrite pwmHighValue = %d", 200);
  EEPROM.put(pwmLowValueAddress, 10);
  printf("\nwrite pwmLowValue = %d", 10);
  printf("\n");

  EEPROM.commit();
}

void readSettings() {
  isOn = boolean(EEPROM.read(isOnAddress));
  printf("\nread isOn = %d", isOn);
  mode = EEPROM.read(modeAddress);  
  printf("\nread mode = %d", mode);
  EEPROM.get(timeIntervalAddress, timeInterval);
  printf("\nread timeInterval = %d", timeInterval);
  EEPROM.get(pwmHighValueAddress, pwmHighValue);
  printf("\nread pwmHighValue = %d", pwmHighValue);
  EEPROM.get(pwmLowValueAddress, pwmLowValue);
  printf("\nread pwmLowValue = %d", pwmLowValue);
  printf("\n");
}