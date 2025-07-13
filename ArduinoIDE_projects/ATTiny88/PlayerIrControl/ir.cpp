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
        case 81: // next track
            mySerial.println("next track button is pressed");
            pinMode(NEXT_TRACK_PIN, OUTPUT);
            digitalWrite(NEXT_TRACK_PIN, 0);
            delay(KEY_PRESS_TIME/2);
            break;
        case 80: // prev track
            mySerial.println("prev track button is pressed");
            pinMode(PREV_TRACK_PIN, OUTPUT);
            digitalWrite(PREV_TRACK_PIN, 0);
            delay(KEY_PRESS_TIME/2);
            break;
          case 64: // on/off
            mySerial.println("power on/off");
            mySerial.println(boolean(digitalRead(PLAYER_POWER_PIN)));
            digitalWrite(PLAYER_POWER_PIN, !boolean(digitalRead(PLAYER_POWER_PIN)));
            break;
      }
 
    } else {
        if (keyPressTimer.isReady()) { // controls releasing button
          mySerial.println("keyPressTimer.isReady()");
          switch(command) {
            case 81: // next track
                mySerial.println("next track  button is released");
                pinMode(NEXT_TRACK_PIN, INPUT);
                break;
            case 80: // prev track
                mySerial.println("prev track  button is released");
                pinMode(PREV_TRACK_PIN, INPUT);
                break;
          }
          keyPressTimer.start();
          command = -1;
      }
    }    
}