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
    Serial.println("DoorSensor");
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

void checkFireSensor() { 
  // Serial.println("checkFireSensor()");
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
