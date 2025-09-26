#define SERIAL_SPEED 115200

#define LED_ADDRESS_PIN D2       
#define NUM_LEDS 20
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

#define MIC_PIN     A0     
#define BRIGHTNESS  255

// Задаём рабочий диапазон микрофона
#define MIN_SOUND_LEVEL  300   // тихо
#define MAX_SOUND_LEVEL  320   // громко
#define TIME_INTERVAL 50

#define SOUND_SCALE 5.0