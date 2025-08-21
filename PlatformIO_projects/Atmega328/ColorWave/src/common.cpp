#include "common.h"

boolean isOn;


// Blinker ledStandbyBlinker = Blinker(MODE_LED_PIN, 2000, 50, &Serial, SERIAL_SPEED);
// Blinker ledAlarmBlinker = Blinker(MODE_LED_PIN, 1000, 500, &Serial, SERIAL_SPEED);
// Blinker beepAlarmBlinker = Blinker(BEEP_SIGNAL_PIN, 1000, 500, &Serial, SERIAL_SPEED);

// int mode;

// void offAllBlinkers() {
//   // Serial.println("offAllBlinkers()");
//   ledAlarmBlinker.setActive(false);
//   beepAlarmBlinker.setActive(false);
//   ledStandbyBlinker.setActive(false);
// }

void shortBeep(int beeps) {
  for (int i = 0; i < beeps; i++) {
    digitalWrite(BEEP_SIGNAL_PIN, 1);  
    delay(50);
    digitalWrite(BEEP_SIGNAL_PIN, 0);
    delay(100);
  }
}

// void setMode(int m) {
//   mode = m;
//   Serial.print("Mode ");  Serial.println(mode); 
//   offAllBlinkers();

//   switch (mode) {
//     case 0: 
//       shortBeep(1);     
//       break; 
//     case 1:
//       shortBeep(2);
//       ledStandbyBlinker.setActive(true);
//       break;  
//     default:
//       break;
//   }  
// }


// void blink() {
//   ledStandbyBlinker.blink();
//   ledAlarmBlinker.blink();
//   beepAlarmBlinker.blink();
// }