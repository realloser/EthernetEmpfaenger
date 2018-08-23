#include <Arduino.h>

#define RECEIVE_LED_PIN 13
#define RECEIVE_PIN = 3

extern uint8_t receivedMessage[];

void setupReceiveData();

bool loopReceiveData();
