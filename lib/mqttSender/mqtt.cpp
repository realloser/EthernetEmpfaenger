
#include <mqtt.h>
#include <SPI.h>
#include <Ethernet.h>
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