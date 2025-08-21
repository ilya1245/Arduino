#include <ir.h>
// #include <ledStrip.h>

NecDecoder ir;
boolean isPrintKeyCode = true;

void irIsr() {
  ir.tick();  
}

void processIr() {
  // Serial.println("\nprocessIr()");
  // delay(waveStepDelay);
  if (ir.available()) {
    // Serial.println("\nprocessIr() if");
    if(isPrintKeyCode) printf("\nKeyCode: %d   \n", ir.readCommand());
    // if(isPrintKeyCode) {
    //   Serial.print("\nKeyCode: ");
    //   Serial.println(ir.readCommand());
    // }

    digitalWrite(RECV_LED_PIN, HIGH);
    delay(20);
    digitalWrite(RECV_LED_PIN, LOW);

    switch(ir.readCommand()) {
      case 104: // star          
          // setMode(1); // on the watch system       
          break;
      case 176: // hash
          // setMode(0); // off the watch system
          break;
      default: // auto
        break;  
    }
  } else {
    // delay(waveStepDelay);
  }
}