#include "bt.h"
#include "action.h"

BluetoothSerial SerialBT;

int mode = 1;

// Разбор команд
void processBtCommand(String cmd) {
  Serial.printf("cmd: %s\n", cmd);
  cmd.trim();  
  if (cmd.startsWith("MODE:")) {
    mode = cmd.substring(5).toInt();
    Serial.printf("Выбран режим: %d\n", mode);
  } 
  else if (cmd.startsWith("UPPER:")) {
    pwmHighValue = cmd.substring(6).toInt();
    Serial.printf("Верхняя яркость: %d%%\n", pwmHighValue);
  } 
  else if (cmd.startsWith("LOWER:")) {
    pwmLowValue = cmd.substring(6).toInt();
    Serial.printf("Нижняя яркость: %d%%\n", pwmLowValue);
  } 
  else if (cmd == "ON") {
    isOn = true;
    Serial.println("Включено");
  } 
  else if (cmd == "OFF") {
    isOn = false;
    Serial.println("Выключено");
  }
}

void processMode(int mode) {

}

void processBT() {
  // Читаем команды с телефона
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    processBtCommand(cmd);
  }
}