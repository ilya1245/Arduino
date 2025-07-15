#include <common.h>

// GTimer lightTimer(MS, ALARM_ON_TIME);
GTimer alarmTimer(MS);
Blinker ledStandbyBlinker = Blinker(MODE_LED_PIN, 2000, 50, &Serial, SERIAL_SPEED);
Blinker ledAlarmBlinker = Blinker(MODE_LED_PIN, 1000, 500, &Serial, SERIAL_SPEED);
Blinker beepAlarmBlinker = Blinker(BEEP_SIGNAL_PIN, 1000, 500, &Serial, SERIAL_SPEED);


// GTimer lcdClearTimer(MS, 3000);

// LiquidCrystal_I2C lcd(0x27, 16, 2);

int mode = 0; // ALARM_OFF 
// boolean lightState = false;

// byte pwmValue = 255;
// byte pwmMinValue = 10;

void offAllBlinkers() {
  // Serial.println("offAllBlinkers()");
  ledAlarmBlinker.setActive(false);
  beepAlarmBlinker.setActive(false);
  ledStandbyBlinker.setActive(false);
}

void setMode(int m) {
  // if (mode == m) return;
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