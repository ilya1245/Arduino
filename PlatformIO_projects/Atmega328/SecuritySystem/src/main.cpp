#include <NecDecoder.h>
#include <LibPrintf.h>
#include <common.h>
#include <ir.h>
#include "controlAlarm.h"

void setup() {
  Serial.begin(SERIAL_SPEED);

  attachInterrupt(0, irIsr, FALLING);
  pinMode(RECV_PIN, INPUT);

  // pinMode(IR_LED_PIN, OUTPUT); 
  pinMode(BEEP_SIGNAL_PIN, OUTPUT);
  digitalWrite(BEEP_SIGNAL_PIN, 0);
  pinMode(MODE_LED_PIN, OUTPUT);  
  digitalWrite(MODE_LED_PIN, 0);

  pinMode(DOOR_SENSOR_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
  pinMode(FIRE_SENSOR_PIN, INPUT);

  alarmTimer.setTimeout(ALARM_ON_TIME);
  alarmTimer.stop();
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





