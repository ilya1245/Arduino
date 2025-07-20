#include <controlLight.h>

void controlLightByState() { 
  if (lightState) {
    analogWrite(LIGHT_PIN, pwmValue);
  } else {
    digitalWrite(LIGHT_PIN, 0);
  }
}

void controlLightByPIR() {
  int sensorValue = digitalRead(PIR_PIN);
  if (!lightTimer.isEnabled() and sensorValue > 0) {    
    lightTimer.start();
    lightState = true;
    controlLightByState();
    Serial.println("lightTimer is started");
  }

  if (lightTimer.isReady() and sensorValue == 0) {
    lightState = false;
    controlLightByState();
    Serial.println("light is off");
    lightTimer.stop();
  }
}

void controlLightBySound() {
  int soundValue = soundValue = analogRead(SOUND_SENSOR_PIN);
  if (soundValue > soudLevelThreshold - 1) {
    Serial.print("soundValue = ");
    Serial.println(soundValue);  

    lcd.setCursor(0,0);  
    lcd.print("soundValue = ");
    lcd.print(soundValue);

    lcdClearTimer.start();
    
    // Serial.println(soundTimer.isReady());
    // Serial.println(soundTimer.isEnabled());
  }
  
  if (soundValue > soudLevelThreshold) {  
    if (!soundTimer.isReady()) return;
    Serial.println("Sound!!!");
    lcd.setCursor(0,1);
    lcd.print("Sound!!!  ");
    lcd.print(soundValue);
    lightState = !lightState;
    controlLightByState();   
    soundTimer.setTimeout(SOUND_CHECK_INTERVAL);
  } 
}

void controlLight() {
  switch(mode) {
      case 1: // up
        // Serial.println("Simple mode");
        controlLightByState();
        break;
      case 2: // down
        // Serial.println("PIR mode");
        controlLightByPIR();
        break;
      case 3: // 1  
        // Serial.println("Sound mode");
        controlLightBySound();
        break;
      default: // auto
        break;
  }
}