#define WIFI_LED_PIN D4
#define SERIAL_SPEED 115200

#define MQTT_SERVER "imiflig.site" // IP твоего брокера
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "NodeMCU_1"

#define LED_PIN D2

extern void callback(char* topic, byte* payload, unsigned int length);