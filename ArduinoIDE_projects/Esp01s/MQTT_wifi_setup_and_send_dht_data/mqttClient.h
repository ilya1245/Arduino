#include <PubSubClient.h>
#include "common.h"

extern PubSubClient mqttClient;

extern void connectClientIfNeeded();
extern void callback(char* topic, byte* payload, unsigned int length);
