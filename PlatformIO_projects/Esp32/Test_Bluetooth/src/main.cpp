#include "Arduino.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int LED1_PIN = 2;   // Встроенный LED
const int LED2_PIN = 4;   // Второй LED

int mode = 1;
int upperBrightness = 100;
int lowerBrightness = 50;
bool ledOn = true;

// Интервалы мигания для 10 режимов (мс)
int intervals[10] = {200, 400, 600, 800, 1000, 150, 300, 450, 700, 900};

unsigned long lastToggle = 0;
bool ledState = false;

// Разбор команд
void parseCommand(String cmd) {
  Serial.printf("cmd: %s\n", cmd);
  cmd.trim();  
  if (cmd.startsWith("MODE:")) {
    mode = cmd.substring(5).toInt();
    Serial.printf("Выбран режим: %d\n", mode);
  } 
  else if (cmd.startsWith("UPPER:")) {
    upperBrightness = cmd.substring(6).toInt();
    Serial.printf("Верхняя яркость: %d%%\n", upperBrightness);
  } 
  else if (cmd.startsWith("LOWER:")) {
    lowerBrightness = cmd.substring(6).toInt();
    Serial.printf("Нижняя яркость: %d%%\n", lowerBrightness);
  } 
  else if (cmd == "ON") {
    ledOn = true;
    Serial.println("Включено");
  } 
  else if (cmd == "OFF") {
    ledOn = false;
    Serial.println("Выключено");
  }
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  Serial.begin(115200);
  SerialBT.begin("ESP32_LED_Control"); // Имя Bluetooth устройства
  Serial.println("Bluetooth готов. Подключайтесь через приложение.");
}

void loop() {
  // Читаем команды с телефона
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    parseCommand(cmd);
  }

  // Если выключено — гасим
  if (!ledOn) {
    analogWrite(LED1_PIN, 0);
    analogWrite(LED2_PIN, 0);
    return;
  }

  // Мигание в зависимости от режима
  unsigned long now = millis();
  if (now - lastToggle >= intervals[mode - 1]) {
    ledState = !ledState;
    analogWrite(LED1_PIN, ledState ? map(upperBrightness, 0, 100, 0, 255) : 0);
    analogWrite(LED2_PIN, ledState ? map(lowerBrightness, 0, 100, 0, 255) : 0);
    lastToggle = now;
  }
}
