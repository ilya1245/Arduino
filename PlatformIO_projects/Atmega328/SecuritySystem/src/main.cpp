#include <NecDecoder.h>
#include <LibPrintf.h>
#include <common.h>
#include <ir.h>
#include "controlAlarm.h"

void setup() {
  Serial.begin(9600);

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

  // pinMode(ALARM_LED_PIN, OUTPUT);
  // digitalWrite(BEEP_SIGNAL_PIN, 0);
  // pinMode(BEEP_POWER_PIN, OUTPUT);
  // digitalWrite(BEEP_POWER_PIN, 1);  
  // pinMode(BEEP_GROUND_PIN, OUTPUT);
  // digitalWrite(BEEP_GROUND_PIN, 0);

  // pinMode(LIGHT_PIN, OUTPUT);
  // digitalWrite(LIGHT_PIN, 0);

  // pinMode(SOUND_SENSOR_PIN, INPUT);
  // pinMode(SOUND_SENSOR_POWER_PIN, OUTPUT);
  // digitalWrite(SOUND_SENSOR_POWER_PIN, 1);  
  // pinMode(SOUND_SENSOR_GROUND_PIN, OUTPUT);
  // digitalWrite(SOUND_SENSOR_GROUND_PIN, 0);

  soundTimer.setTimeout(ALARM_ON_TIME);

  // lcd.init();
  // lcd.backlight();
  // lcd.setCursor(0, 0);
  // lcd.print("Hello!");
}

void loop() {
  checkDoorSensor();
  // processIr();
  // controlLight();

  // if (lcdClearTimer.isReady()) lcd.clear();
}





