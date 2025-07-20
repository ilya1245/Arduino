#include <NecDecoder.h>
#include <Arduino.h>
#include <common.h>
#include <controlLight.h>

#define RECV_PIN 2

extern NecDecoder ir;
extern boolean isPrintKeyCode;

extern void irIsr();

extern void processIr();