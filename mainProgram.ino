#include "mainProgram.h"

void setPins(){
	pinMode(LIGHT_POWER_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_POWER_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT);
	pinMode(SOIL_MOISTURE_ANALOG_PIN, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
	digitalWrite(PUMP_PIN, LOW);
	digitalWrite(LIGHT_POWER_PIN, LOW);
}

int calculateTimeToMillis(int hour, int minute, int second){
	return ((hour*60+minute)*60+second)*1000;
}

void setClock(){
	int* timeFromUser = getTimeFromUser();
	clock = calculateTimeToMillis(timeFromUser[0], timeFromUser[1], timeFromUser[2]);
}

void resetClock(){
	int millisInADay = calculateTimeToMillis(24, 0, 0);
	if(clock > millisInADay)
		clock -= millisInADay;
}

void setLightOnTime(){
	int* timeFromUser = getTimeFromUser();
	lightOnTime = calculateTimeToMillis(timeFromUser[0], timeFromUser[1], timeFromUser[2]);
}

void setLightOffTime(){
	int* timeFromUser = getTimeFromUser();
	lightOffTime = calculateTimeToMillis(timeFromUser[0], timeFromUser[1], timeFromUser[2]);
}

void setCheckSoilMoistureTime(){
	int* timeFromUser = getTimeFromUser();
	checkSoilMoistureTime = calculateTimeToMillis(timeFromUser[0], timeFromUser[1], timeFromUser[2]);
}

void toggleLightWhenTime()
{
	if(clock > lightOnTime && clock < lightOffTime){
		digitalWrite(LIGHT_POWER_PIN, LOW);
	} else{
		digitalWrite(LIGHT_POWER_PIN, HIGH);
	}
}

void mesureSoilMoistureWhenTime()
{
	if(clock > checkSoilMoistureTime && clock < checkSoilMoistureTime+10000)
	{
		digitalWrite(SOIL_MOISTURE_POWER_PIN, HIGH);
		delay(100);
		if(digitalRead(SOIL_MOISTURE_DIGITAL_PIN) == LOW)
			pumpWater();
		digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
	}
}

void pumpWater()
{
	byte timeOut = 0;
	while(timeOut == 10)
	{
		digitalWrite(PUMP_PIN, HIGH);
		timeOut += 1;
		delay(1000);
	}
	digitalWrite(PUMP_PIN, LOW);
}
