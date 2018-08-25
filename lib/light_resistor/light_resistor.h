#include <Arduino.h>

#define LIGHTSENSOR_PIN A0

#ifndef INPUT_VOLTAGE
//#define INPUT_VOLTAGE 504 // 5.04 volt on the uno multiplied by ten since map() works with long
#define INPUT_VOLTAGE -1 // define voltage read from the board.
#endif

// extern int inputVoltage;
extern int lightIntensity; 

void setupLightIntensity();

void readLightIntensity();