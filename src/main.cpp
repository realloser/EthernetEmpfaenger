
#include <Arduino.h>
#include "main.h"
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <my_dht.h>
#include <light_resistor.h>
#include <bmp280.h>
#include <receive_data.h>
#include <delayAsync.h>
#include <ethernetSender.h>

#define RECIVER true

void setup()
{
  Serial.begin(9600);
  setupDelayAsync(2 * 60);
  setupBMP();
  setupDHT();
  inputVoltage = 503; // 423 volt on the nano on the breadboard
  setupLightIntesnity();
  setupReceiveData();


  readAllSensors();

  setupEthernet();
}

void readLoop()
{
  if (delayCheck())
  {
    readAllSensors();
  }
}

void loop()
{
  readLoop();
  loopReceiveData();
  loopEthernet();
}


void readAllSensors() {
    readBMP();
    readDHT();
    readLightIntensity();
    Serial.println();
}
