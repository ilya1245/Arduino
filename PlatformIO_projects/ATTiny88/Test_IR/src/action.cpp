#include "action.h"
#include "ATtinySerialOut.h"

void selectAction(uint8_t irCommand) {
  Serial.print("irCommand: ");
  Serial.println(irCommand);
}