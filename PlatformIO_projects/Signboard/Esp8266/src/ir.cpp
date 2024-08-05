#include "ir.h"
#include "action.h"
#include "tune.h"

int debounceTime = 300;
unsigned long currentTime, lastTime;
uint16_t irCommand = 0;
decode_results results;

IRrecv irrecv(RECV_PIN);


void processIr() {
  //  Serial.println("processIr() - start");
  if (irrecv.decode(&results)) {
    Serial.println("processIr() - IrReceiver.decode()");
    digitalWrite(RECV_LED_PIN, 1);
    delay(20);
    digitalWrite(RECV_LED_PIN, 0);
    irrecv.resume(); // Receive the next value
    currentTime = millis();
    if ((currentTime - lastTime) >= debounceTime) {
      if (isPrintKeyCode) printf("results.command: %d\n", results.command);
      if (results.command != 0) irCommand = results.command;
      //      Serial.println(irCommand);
      if (isPrintKeyCode) printf("KeyCode: %d\n", irCommand);
      lastTime = currentTime;
      switch (irCommand) {
        case 20: // on/off
          Serial.println("on/off");
          isSwitchMode = true;
          onOff();
          break;
        case 22: // key 1
          Serial.println("key 1");
          isSwitchMode = true;
          blinkAll(timeInterval * 2, timeInterval * 1.6);
          break;
        case 23: // key 2
          Serial.println("key 2");
          isSwitchMode = true;
          blinkAll(timeInterval * 2, timeInterval);
          break;
        case 24: // key 3
          Serial.println("key 3");
          isSwitchMode = true;
          blinkAll(timeInterval * 2, 100);
          break;
        case 25: // key 4
          Serial.println("key 4");
          isSwitchMode = true;
          blinkAll(timeInterval * 2, 50, 100, 2);
          break;
        case 26: // key 5
          Serial.println("key 5");
          isSwitchMode = true;
          waveAll();
          break;
        case 27: // key 6
          Serial.println("key 6");
          isSwitchMode = true;
          waveLeftToRight();
          break;
        case 28: // key 7
          Serial.println("key 7");
          isSwitchMode = true;
          waveLeftToLeft();
          break;
        case 29: // key 8
          Serial.println("key 8");
          isSwitchMode = true;
          waveRightToLeft();
          break;
        case 30: // key 9
          Serial.println("key 9");
          isSwitchMode = true;
          waveRightToRight();
          break;
        case 31: // key 0
          Serial.println("key 0");
          isSwitchMode = true;
          blinkAll(timeInterval * 2, timeInterval * 2);
          break;
        case 9: // setup
          Serial.println("key setup");
          isSwitchMode = true;
          setup(timeInterval * 8, 50, timeInterval);
          break;
        case 18: // key left Up
          Serial.println("key left Up");
          tunePwmHighValue(pwmStepValue);
          break;
        case 21: // key left Down
          Serial.println("key left Down");
          tunePwmHighValue(-pwmStepValue);
          break;
        case 16: // key right Up
          Serial.println("key right Up");
          tunePwmLowValue(pwmStepValue);
          break;
        case 19: // key right Down
          Serial.println("key right Down");
          tunePwmLowValue(-pwmStepValue);
          break;
        case 11: // key Left
          Serial.println("key Left");
          tuneTimeInterval(-timeStep);
          break;
        case 13: // key Right
          Serial.println("key Right");
          tuneTimeInterval(timeStep);
          break;
      }
      Serial.println("---------------");
      //      irCommand = 0;
    }
  }
  //  Serial.println("processIr() - end");
}