#include <light_resistor.h>

int lightIntensityMeasured; // variable to store the value coming from the sensor
int lightIntensity; 
int inputVoltage = INPUT_VOLTAGE;

void setupLightIntensity(){
  // nothing to do
  lightIntensityMeasured = 0;
  lightIntensity = 0;
}

void readLightIntensity(){
  lightIntensityMeasured = analogRead(LIGHTSENSOR_PIN); // read the value from the sensor
  lightIntensity = map(lightIntensityMeasured, 0, inputVoltage, 0, 500); // normalize the sensor reading
  Serial.print("Lightintensity = ");
  Serial.println(lightIntensity);
}
