

// we have to overwrite the BPM280 address
#define BMP280_ADDRESS 0x76

extern float bmpTemperature;
extern float bmpPressure;

void setupBMP();

void readBMP();