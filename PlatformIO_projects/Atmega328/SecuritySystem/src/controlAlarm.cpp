#include <controlAlarm.h>

void startAlarmSignal() { 
  Serial.println("startAlarmSignal()");
  alarmTimer.start();
  ledStandbyBlinker.setActive(false);
  ledAlarmBlinker.setActive(true);
  beepAlarmBlinker.setActive(true);
}

void checkDoorSensor() {
  if (digitalRead(DOOR_SENSOR_PIN) == LOW) {
    // Serial.println("DoorSensor");
    // Serial.println(alarmTimer.isEnabled());
    if (alarmTimer.isEnabled() == 0) {
      startAlarmSignal();
    } 
  } 
}

void checkIrSensor() { 
  if (digitalRead(IR_SENSOR_PIN) == HIGH) {
    Serial.println("IrSensor");
    if (alarmTimer.isEnabled() == 0) {    
      startAlarmSignal();
    }     
  } 
}

void 

checkFireSensor() { 
  if (digitalRead(FIRE_SENSOR_PIN) == HIGH) {
    Serial.println("FireSensor");
    Serial.println(alarmTimer.isEnabled());
    if (alarmTimer.isEnabled() == 0) {
      startAlarmSignal();
    }    
  } 
}

void checkVibraSensor() { 
  if (digitalRead(VIBRATION_SENSOR_PIN) == HIGH) {
    Serial.println("VibraSensor");
    if (alarmTimer.isEnabled() == 0) {
      startAlarmSignal();
    }    
  } 
}


void checkSensors() { 
  checkFireSensor();
  if (mode == 1) {
    checkDoorSensor();
    checkIrSensor();  
    checkVibraSensor();
  }

}




// void stopAlarmSignal() {
//   offAllBlinkers();
// }





// void controlLightByPIR() {
//   int sensorValue = digitalRead(PIR_PIN);
//   if (!lightTimer.isEnabled() and sensorValue > 0) {    
//     lightTimer.start();
//     lightState = true;
//     // controlLightByState();
//     Serial.println("lightTimer is started");
//   }

//   if (lightTimer.isReady() and sensorValue == 0) {
//     lightState = false;
//     // controlLightByState();
//     Serial.println("light is off");
//     lightTimer.stop();
//   }
// }

// void controlLightBySound() {
//   int soundValue = soundValue = analogRead(SOUND_SENSOR_PIN);
//   if (soundValue > 21) {
//     Serial.print("soundValue = ");
//     Serial.println(soundValue);  

//     lcd.setCursor(0,0);  
//     lcd.print("soundValue = ");
//     lcd.print(soundValue);

//     lcdClearTimer.start();
    
//     // Serial.println(soundTimer.isReady());
//     // Serial.println(soundTimer.isEnabled());
//   }
  
//   if (soundValue > 22) {  
//     if (!soundTimer.isReady()) return;
//     Serial.println("Sound!!!");
//     lcd.setCursor(0,1);
//     lcd.print("Sound!!!  ");
//     lcd.print(soundValue);
//     lightState = !lightState;
//     controlLightByState();   
//     soundTimer.setTimeout(SOUND_CHECK_INTERVAL);
//   } 
// }

// void controlLight() {
//   switch(mode) {
//       case 1: // up
//         // Serial.println("Simple mode");
//         controlLightByState();
//         break;
//       case 2: // down
//         // Serial.println("PIR mode");
//         controlLightByPIR();
//         break;
//       case 3: // 1  
//         // Serial.println("Sound mode");
//         controlLightBySound();
//         break;
//       default: // auto
//         break;
//   }
// }