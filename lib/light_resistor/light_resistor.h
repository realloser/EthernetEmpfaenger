#include <Arduino.h>

#define LIGHTSENSOR_PIN A0
//#define INPUT_VOLTAGE 504 // 5.04 volt on the uno multiplied by ten since map() works with long
#define INPUT_VOLTAGE 0 // define voltage read from the board.
#define REFERENCE_VOLTAGE 500 // 5.0 volt exected

extern int inputVoltage;
extern int lightIntensity; 

void setupLightIntensity();

void readLightIntensity();