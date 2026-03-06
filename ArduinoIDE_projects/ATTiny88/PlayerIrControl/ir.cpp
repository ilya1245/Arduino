#include "ir.h"
#include "TinyIRReceiver.hpp"

int command;

void initIr() {
  initPCIInterruptForTinyReceiver(); // ← без аргументов!
}

void processIr() {
  if (TinyReceiverDecode()) {
    command = TinyIRReceiverData.Command;
    digitalWrite(IR_LED_PIN, 1);
    delay(20);
    digitalWrite(IR_LED_PIN, 0);
    mySerial.print("IR command: ");
    mySerial.println(command);

    switch(command) { // controls pressing button 
      case IR_NEXT_TRACK_VOL_UP_CODE: // next track
          mySerial.println("next track button is pressed");
          pinMode(NEXT_TRACK_PIN, OUTPUT);
          digitalWrite(NEXT_TRACK_PIN, 0);
          delay(KEY_PRESS_TIME/2);
          break;
      case IR_PREV_TRACK_VOL_DOWN_CODE: // prev track
          mySerial.println("prev track button is pressed");
          pinMode(PREV_TRACK_PIN, OUTPUT);
          digitalWrite(PREV_TRACK_PIN, 0);
          delay(KEY_PRESS_TIME/2);
          break;
      case IR_ON_OFF_CODE: // on/off
        mySerial.println("power on/off");
        mySerial.println(boolean(digitalRead(PLAYER_POWER_PIN)));
        digitalWrite(PLAYER_POWER_PIN, !boolean(digitalRead(PLAYER_POWER_PIN)));
        break;
    }
    keyPressTimer.start();
  } else {
    if (keyPressTimer.isReady()) { // controls releasing button
      // mySerial.println("keyPressTimer.isReady()");
      switch(command) {
        case IR_NEXT_TRACK_VOL_UP_CODE: // next track
            mySerial.println("next track button is released");
            pinMode(NEXT_TRACK_PIN, INPUT);
            break;
        case IR_PREV_TRACK_VOL_DOWN_CODE: // prev track
            mySerial.println("prev track button is released");
            pinMode(PREV_TRACK_PIN, INPUT);
            break;
      }
      keyPressTimer.start();
      command = -1;
    }
  }    
}