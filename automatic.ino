#include "automatic.h"

void setPins(){
	pinMode(LIGHT_POWER_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_POWER_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT);
	pinMode(SOIL_MOISTURE_ANALOG_PIN, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
	digitalWrite(PUMP_PIN, LOW);
	digitalWrite(LIGHT_POWER_PIN, LOW);
}

int calculateTimeToMillis(int hour, int minute, int second){
	return ((hour*60+minute)*60+second)*1000;
}

void setClock(){
	struct Time t = getTimeFromUser();
	clock = calculateTimeToMillis(t.hours, t.minuts, t.seconds);
}

void resetClock(){
	int millisInADay = calculateTimeToMillis(24, 0, 0);
	if(clock > millisInADay){
		clock -= millisInADay;
		checkedSoilMoistureToDay = false;
	}
}

void setLightOnTime(){
	struct Time t = getTimeFromUser();
	lightOnTime = calculateTimeToMillis(t.hours, t.minuts, t.seconds);
}

void setLightOffTime(){
	struct Time t = getTimeFromUser();
	lightOffTime = calculateTimeToMillis(t.hours, t.minuts, t.seconds);
}

void setCheckSoilMoistureTime(){
	struct Time t = getTimeFromUser();
	checkSoilMoistureTime = calculateTimeToMillis(t.hours, t.minuts, t.seconds);
}

void toggleLightWhenTime()
{
	if(clock >= lightOnTime && clock <= lightOffTime){
		if(lightIsOn == true)
			return;
		lightIsOn = true;
		digitalWrite(LIGHT_POWER_PIN, LOW);
	} else{
		if(lightIsOn == false)
			return;
		lightIsOn = false;
		digitalWrite(LIGHT_POWER_PIN, HIGH);
	}
}

void mesureSoilMoistureWhenTime()
{
	if(clock > checkSoilMoistureTime && checkedSoilMoistureToDay == false)
	{
		checkedSoilMoistureToDay = true;
		digitalWrite(SOIL_MOISTURE_POWER_PIN, HIGH);
		delay(100);
		if(digitalRead(SOIL_MOISTURE_DIGITAL_PIN) == LOW)
			pumpWater();
		digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
	}
}

void pumpWater()
{
	int timeOut = 0;
	digitalWrite(PUMP_PIN, HIGH);
	while(digitalRead(SOIL_MOISTURE_DIGITAL_PIN) == LOW || timeOut >= 30)
	{
		timeOut += 5;
		delay(5000);
	}
	digitalWrite(PUMP_PIN, LOW);
}
