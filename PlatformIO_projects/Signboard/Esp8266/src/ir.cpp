#include "ir.h"
#include "action.h"
// #include "tune.h"

unsigned int debounceTime = 300;
unsigned long currentTime, lastTime;
byte irCommand = 0;
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
      selectAction(irCommand);
      Serial.println("---------------");
      //      irCommand = 0;
    }
  }
  //  Serial.println("processIr() - end");
}