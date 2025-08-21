#include "store.h"
// #include "common.h"
// #include "tune.h"

// int isOnAddress = 0;
// int ledModeIrCommandAddress = 2;
// int timeIntervalAddress = 4;
// int pwmHighValueAddress = 8;
// int pwmLowValueAddress = 12;



void writeSettings() {
  EEPROM.write(IS_ON_ADDRESS, byte(isOn));
  printf("\nwrite isOn = %d", byte(isOn));

  EEPROM.put(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  printf("\nwrite waveStepDelay = %d", waveStepDelay);  

  EEPROM.put(WAVE_GRADIENT_ADDRESS, waveGradient);
  printf("\nwrite waveGradient = %d\n", waveGradient); 
}

void writeDefaultSettings() {
  isOn = 1;
  EEPROM.write(IS_ON_ADDRESS, isOn);
  printf("\nwrite isOn = %d", isOn);

  waveStepDelay = (WAVE_STEP_DELAY_MAX + WAVE_STEP_DELAY_MIN) / 2;
  EEPROM.put(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  printf("\nwrite waveStepDelay = %d", waveStepDelay);  

  waveGradient = (WAVE_GRADIENT_MAX + WAVE_GRADIENT_MIN) / 2;
  EEPROM.put(WAVE_GRADIENT_ADDRESS, waveGradient);
  printf("\nwrite waveGradient = %d\n", waveGradient); 
}

void readSettings() {
  isOn = boolean(EEPROM.read(IS_ON_ADDRESS));
  printf("\nread isOn = %d", isOn);

  waveStepDelay = EEPROM.get(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  printf("\nread waveStepDelay = %d", waveStepDelay);

  EEPROM.get(WAVE_GRADIENT_ADDRESS, waveGradient);
  printf("\nread waveGradient = %d\n", waveGradient);

  ledStepTimer.setInterval(waveStepDelay);
}