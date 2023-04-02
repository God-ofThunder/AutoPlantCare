#ifndef AUTOMATIC_H
#define AUTOMATIC_H

#define LIGHT_POWER_PIN (A1)
#define SOIL_MOISTURE_ANALOG_PIN (A0)
#define SOIL_MOISTURE_DIGITAL_PIN (11)
#define SOIL_MOISTURE_POWER_PIN (7)
#define BATTERY_LEVEL_BORD_PIN (A7)
#define BATTERY_LEVEL_PUMP_PIN (A6)
#define PUMP_PIN (A2)

// the clock ana the time were the light turns on and off 
// and the time were it checks soil moisture is set to default values
// it can be changed by the serial conection 
// but it will be reset evry time you conect to the board
int clock = 43200000; // 12:00
int lightOnTime = 14400000; // 4:00
int lightOffTime = 68400000; // 19:00
int checkSoilMoistureTime = 21600000; // 6:00
bool lightIsOn = true;
bool checkedSoilMoistureToDay = false;

struct Time{
	int hours;
	int minuts;
	int seconds;
};

void setPins();
int calculateTimeToMillis(int, int, int);
void setClock();
void resetClock();
void setLightOnTime();
void setLightOffTime();
void setCheckSoilMoistureTime();
void toggleLightWhenTime();
void mesureSoilMoistureWhenTime();
void pumpWater();
#endif
