#include <NecDecoder.h>
#include <LibPrintf.h>
#include <common.h>
#include <ir.h>
#include "controlAlarm.h"

void setup() {
  Serial.begin(SERIAL_SPEED);

  attachInterrupt(0, irIsr, FALLING);
  pinMode(RECV_PIN, INPUT);

  pinMode(DOOR_SENSOR_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
  pinMode(FIRE_SENSOR_PIN, INPUT);

  alarmTimer.setTimeout(ALARM_ON_TIME);
  setMode(0);
}

void loop() {
  checkSensors();  
  processIr();
  
  if (alarmTimer.isReady()) {
    Serial.println("alarmTimer.isReady()");    
    offAllBlinkers();
    alarmTimer.stop();
    if (mode == 1) ledStandbyBlinker.setActive(true);
  } 

  blink();
}





