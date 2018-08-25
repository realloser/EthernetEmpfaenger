
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

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define MQTT_CLIENT_ID "UNO_CLIENT"

// Update these with values suitable for your network.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 123);
IPAddress server(192, 168, 1, 169);
#include <PubSubClient.h>
EthernetClient ethClient;
PubSubClient client(ethClient);

bool reconnectMQTT()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID))
    {
      Serial.println("connected");
      return true;
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      return false;
    }
  }
  return true;
}

void publishMQTT(char *message)
{
  if (reconnectMQTT())
  {
    Serial.print("Publish message: ");
    Serial.println(message);

    client.publish("M18/Environment", message);
  }
}

void setupMQTT()
{
  client.setServer(server, 1883);
  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

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
