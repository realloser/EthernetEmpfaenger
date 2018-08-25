
#ifndef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID "DEFINE_CLIENT_ID"
#endif

#include <Ethernet.h>

// Update these with values suitable for your network.
extern byte mac[];;
extern IPAddress ip;
extern IPAddress server;

bool reconnectMQTT();

void publishMQTT(char *message);

void setupMQTT();