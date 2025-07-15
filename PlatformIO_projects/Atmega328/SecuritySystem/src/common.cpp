#include <common.h>

GTimer alarmTimer(MS);
Blinker ledStandbyBlinker = Blinker(MODE_LED_PIN, 2000, 50, &Serial, SERIAL_SPEED);
Blinker ledAlarmBlinker = Blinker(MODE_LED_PIN, 1000, 500, &Serial, SERIAL_SPEED);
Blinker beepAlarmBlinker = Blinker(BEEP_SIGNAL_PIN, 1000, 500, &Serial, SERIAL_SPEED);

int mode;

void offAllBlinkers() {
  // Serial.println("offAllBlinkers()");
  ledAlarmBlinker.setActive(false);
  beepAlarmBlinker.setActive(false);
  ledStandbyBlinker.setActive(false);
}

void setMode(int m) {
  mode = m;
  Serial.print("Mode ");  Serial.println(mode); 
  digitalWrite(BEEP_SIGNAL_PIN, 1);  
  delay(50);
  digitalWrite(BEEP_SIGNAL_PIN, 0);
  offAllBlinkers();

  switch (mode) {
    case 0:      
      break; 
    case 1:
      ledStandbyBlinker.setActive(true);
      break;  
    default:
      break;
  }
}

void blink() {
  ledStandbyBlinker.blink();
  ledAlarmBlinker.blink();
  beepAlarmBlinker.blink();
}