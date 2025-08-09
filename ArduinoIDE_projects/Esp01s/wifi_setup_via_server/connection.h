#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// #include <LibPrintf.h>
// #include <WiFiMultiStable.h>
#include "common.h"
#include "blink.h"
#include "accessPoint.h"

// extern WiFiMultiStable wiFiMultiStable;
// extern PubSubClient mqttClient;

extern int activeWifiId;
extern const char* mqttTopicSwitcher;

extern void tryConnect();
extern void connectClientIfNeeded();
extern void callback(char* topic, byte* payload, unsigned int length);
extern void showWifiStatus();

