#include "automatic.h"
#include "serialInterface.h"

void setup()
{
	setSerial();
	setPins();
}

int startTime;
void loop()
{
	startTime = millis();
	getIndput();
	delay(1000);
	if(manualMode == false){
		toggleLightWhenTime();
		mesureSoilMoistureWhenTime();
	}
	//resets clock if its a new day
	resetClock();
	clock += millis()-startTime;

}
