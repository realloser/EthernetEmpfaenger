#include <Arduino.h>
#include <delayAsync.h>

unsigned long interval; // interval at which to read (milliseconds)
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last delay was updated
unsigned long currentMillis;

void setupDelayAsync(int timespanSeconds) {
  interval = 1000ul * timespanSeconds;
  Serial.print("Delay set to: ");
  Serial.println(interval);
}

bool delayCheck()
{
  // check to see if the delay has passed; that is, if the difference
  // between the current time and last time
  currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time delay
    previousMillis = currentMillis;
    return true;
  }
  else
  {
    return false;
  }
}
