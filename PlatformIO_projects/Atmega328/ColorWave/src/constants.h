#define SERIAL_SPEED 9600
#define RECV_PIN 2
#define RECV_LED_PIN 12
#define BEEP_SIGNAL_PIN 4

#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define LED_ADDRESS_PIN 6
#define NUM_LEDS 50   // в твоей ленте 60 диодов = 20 адресных "пикселей" на метр

#define IS_ON_ADDRESS 0
#define WAVE_STEP_DELAY_ADDRESS 1
#define WAVE_GRADIENT_ADDRESS 3
#define BASE_COLOR_STEP_ADDRESS 5

#define WAVE_STEP_DELAY_MIN NUM_LEDS*1.5
#define WAVE_STEP_DELAY_MAX 500
#define WAVE_STEP_DELAY_STEP 20

#define WAVE_GRADIENT_MIN 0
#define WAVE_GRADIENT_MAX 20
#define WAVE_GRADIENT_STEP 1

#define BASE_COLOR_STEP_INIT 3







// #define MODE_LED_PIN 3
// #define BEEP_SIGNAL_PIN 4

// #define FIRE_SENSOR_PIN 7
// #define IR_SENSOR_PIN 8
// #define VIBRATION_SENSOR_PIN 9
// #define DOOR_SENSOR_PIN 10

// #define ALARM_ON_TIME 5000
