/*
 Basic MQTT example with Authentication

  - connects to an MQTT server, providing username
    and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include <MQTT.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 191);
IPAddress server(192, 168, 1, 169);

EthernetClient ethClient;
PubSubClient client(ethClient);

void setupMqttSender()
{
  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);
  if(client.connect(MQTT_CLIENT_ID)){
    Serial.println("Connected to MQTT server");
  }
  else {
    Serial.println("Failed to connect to MQTT server");
  }


}

bool publishMessage(char *message)
{
  if(!client.connected()) {
    if(!client.connect(MQTT_CLIENT_ID)){
      // failed to connect to the server
      Serial.println("Failed to re-connect to MQTT server");
      return false;
    }
    Serial.println("Re-connected to MQTT server");
  }

  if(!client.publish("M18/Environment", message)){
    Serial.println("Failed to published message to MQTT server");
    return false;
  }

  Serial.println("Successfully published message to MQTT server");
  Serial.println(message);
  return true;
  
}