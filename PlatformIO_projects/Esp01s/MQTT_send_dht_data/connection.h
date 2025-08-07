#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LibPrintf.h>
#include <WiFiMultiStable.h>
#include "common.h"
#include "blink.h"

extern WiFiMultiStable wiFiMultiStable;
extern PubSubClient mqttClient;

extern int activeWifiId;
extern const char* mqttTopicSwitcher;

extern void connectToMQTT();
extern void connectClientIfNeeded();


