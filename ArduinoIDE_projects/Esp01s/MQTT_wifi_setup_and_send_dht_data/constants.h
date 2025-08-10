#define WIFI_LED_PIN 0
#define SERIAL_SPEED 115200

#define MQTT_SERVER "imiflig.site" // IP твоего брокера
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "esp01s_1"
#define MQTT_TEMPERATURE_TOPIC "esp01s_meteo_1/dht11/temperature"
#define MQTT_HUMIDITY_TOPIC "esp01s_meteo_1/dht11/humidity"
#define MQTT_TEMPERATURE_CORRECTION_COMMAND_TOPIC "esp01s/temperature/correction/set"

// #define LED_PIN D2
#define DHTPIN 2
#define DHTTYPE DHT11

#define EEPROM_SIZE 512
#define EEPROM_FLAG_ADDR 0
#define EEPROM_SSID_LEN_ADDR 1
#define EEPROM_PASS_LEN_ADDR 2
#define EEPROM_DATA_ADDR 3

#define HOST_TO_PING "8.8.8.8"

