#include "store.h"

void writeSettings() {
  EEPROM.write(IS_ON_ADDRESS, byte(isOn));
  Serial.printf("\nwrite isOn = %d", byte(isOn));

  EEPROM.put(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  Serial.printf("\nwrite waveStepDelay = %d", waveStepDelay);  

  EEPROM.put(WAVE_GRADIENT_ADDRESS, waveGradient);
  Serial.printf("\nwrite waveGradient = %d", waveGradient); 

  EEPROM.commit();
}

void writeDefaultSettings() {
  isOn = 1;
  EEPROM.write(IS_ON_ADDRESS, isOn);
  Serial.printf("\nwrite isOn = %d", isOn);

  waveStepDelay = (WAVE_STEP_DELAY_MAX + WAVE_STEP_DELAY_MIN) / 2;
  EEPROM.put(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  Serial.printf("\nwrite waveStepDelay = %d", waveStepDelay);  

  waveGradient = 10;
  EEPROM.put(WAVE_GRADIENT_ADDRESS, waveGradient);
  Serial.printf("\nwrite waveGradient = %d", waveGradient);  

  EEPROM.commit();
  ledStepTimer.setInterval(waveStepDelay);
}

void readSettings() {
  isOn = boolean(EEPROM.read(IS_ON_ADDRESS));
  Serial.printf("\nread isOn = %d", isOn);

  EEPROM.get(WAVE_STEP_DELAY_ADDRESS, waveStepDelay);  
  Serial.printf("\nread waveStepDelay = %d", waveStepDelay);

  EEPROM.get(WAVE_GRADIENT_ADDRESS, waveGradient);
  Serial.printf("\nread waveGradient = %d", waveGradient);

  ledStepTimer.setInterval(waveStepDelay);
}