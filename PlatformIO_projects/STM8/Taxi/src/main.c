#include <ir.h>

void setup() {
  Serial_begin(9600);
  pinMode(PWM_PIN, OUTPUT); 
  pinMode(RECV_PIN, INPUT);
  pinMode(RECV_LED_PIN, OUTPUT);
  // printf("IR receiver ready\n");
}



void loop() {
  // printf("loop()\n");
  processIr();
  // printf("loop() - doWave()\n");
  doWave();  
}



