#include <VirtualWire.h>

#include <receive_data.h>

const int led_pin = RECEIVE_LED_PIN;
const int receive_pin = 3;

uint8_t buflen = VW_MAX_MESSAGE_LEN;
uint8_t receivedMessage[VW_MAX_MESSAGE_LEN];

void setupReceiveData()
{
  Serial.println("Setup Receive Data");
  delay(1000);

  // Initialise the IO and ISR
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);            // Bits per sec

  vw_rx_start(); // Start the receiver PLL running
  Serial.println("Ready to receive data");
}

bool loopReceiveData()
{
  if (vw_get_message(receivedMessage, &buflen)) // Non-blocking
  {
    Serial.println("Received data");

    digitalWrite(led_pin, HIGH); // Flash a light to show received good message

    Serial.print("Received: ");
    Serial.println((char *)receivedMessage);
    digitalWrite(led_pin, LOW);
    return true;
  }
  return false;
}
