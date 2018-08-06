#include <VirtualWire.h>

#include <receive_data.h>

const int led_pin = RECEIVE_LED_PIN;
const int receive_pin = 3;

uint8_t buflen = VW_MAX_MESSAGE_LEN;
uint8_t receivedMessage[VW_MAX_MESSAGE_LEN];

void setupReceiveData()
{
    delay(1000);

    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loopReceiveData()
{
   

    if (vw_get_message(receivedMessage, &buflen)) // Non-blocking
    {
      	int i;

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
      	// Message with a good checksum received, print it.
      	Serial.print("Got: ");

      	for (i = 0; i < buflen; i++)
      	{
      	    Serial.print(receivedMessage[i], HEX);
      	    Serial.print(' ');
      	}
      	Serial.println();

        for (i = 0; i < buflen; i++)
      	{
           if (receivedMessage[i] == '\0')
           {
             break;
           }
      	   Serial.print((char)receivedMessage[i]);
      	}
      	Serial.println();

        digitalWrite(led_pin, LOW);
    }
}
