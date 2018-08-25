
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

#include <Ethernet.h>
#include <mqtt.h>
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 123);
IPAddress server(192, 168, 1, 169);


void setup()
{
  Serial.begin(9600);
  setupDelayAsync(2 * 5);
  setupBMP();
  setupDHT();
  inputVoltage = 503; // 423 volt on the nano on the breadboard
  setupLightIntensity();
  setupReceiveData();

  readAllSensors();

  setupMQTT();
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
}

char transmissionMessage[50];
unsigned int messageIndex;
void readAllSensors()
{
  readBMP();
  readDHT();
  readLightIntensity();

  // multiply the readings by factor 100 so we can just send the int.
  // node name, message index, primary temp, humidity, light intensity, voltage if any, secondary temp, air pressure
  sprintf(transmissionMessage, "%s|%i|%i|%i|%i|%i|%i|%lu",
          NODE_HASH, messageIndex++, (int)(dhtTemp * 100), (int)(dhtHum * 100), lightIntensity,
          -1, (int)(bmpTemperature * 100), (unsigned long)(bmpPressure * 100));

  publishMQTT(transmissionMessage);
}
