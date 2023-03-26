#ifndef MAINPROGRAM_H
#define MAINPROGRAM_H

#define LIGHT_POWER_PIN (A1)
#define SOIL_MOISTURE_ANALOG_PIN (A0)
#define SOIL_MOISTURE_DIGITAL_PIN (11)
#define SOIL_MOISTURE_POWER_PIN (7)
#define BATTERY_LEVEL_BORD_PIN (A7)
#define BATTERY_LEVEL_PUMP_PIN (A6)
#define PUMP_PIN (A2)

int clock = 0;
int lightOnTime = 0;
int lightOffTime = 0;
int checkSoilMoistureTime = 0;
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
