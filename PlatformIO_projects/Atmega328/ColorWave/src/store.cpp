#include "store.h"

void writeSettings() {
  EEPROM.write(IS_ON_ADDRESS, byte(isOn));
  printf("\nwrite isOn = %d", byte(isOn));

  EEPROM.put(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  printf("\nwrite waveStepDelay = %d", waveStepDelay);  

  EEPROM.put(WAVE_GRADIENT_ADDRESS, waveGradient);
  printf("\nwrite waveGradient = %d", waveGradient); 

  EEPROM.put(BASE_COLOR_STEP_ADDRESS, baseColorStep);
  printf("\nwrite baseColorStep = %d\n", baseColorStep); 
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
  printf("\nwrite waveGradient = %d", waveGradient);

  baseColorStep = BASE_COLOR_STEP_INIT;
  EEPROM.put(BASE_COLOR_STEP_ADDRESS, baseColorStep);
  printf("\nwrite baseColorStep = %d\n", baseColorStep);
}

void readSettings() {
  isOn = boolean(EEPROM.read(IS_ON_ADDRESS));
  printf("\nread isOn = %d", isOn);

  EEPROM.get(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  printf("\nread waveStepDelay = %d", waveStepDelay);

  EEPROM.get(WAVE_GRADIENT_ADDRESS, waveGradient);
  printf("\nread waveGradient = %d", waveGradient);

  EEPROM.get(BASE_COLOR_STEP_ADDRESS, baseColorStep);
  printf("\nread baseColorStep = %d\n", baseColorStep);

  ledStepTimer.setInterval(waveStepDelay);
}