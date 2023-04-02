#include "tests.h"
// Manual mode
void turnOnLight_manualMode(){
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(LIGHT_POWER_PIN, LOW);
	lightIsOn = true;
	Serial.print("Light is on\n");
}

void turnOffLight_manualMode(){
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(LIGHT_POWER_PIN, HIGH);
	lightIsOn = false;
	Serial.print("Light is off\n");
}

void pumpWater_manualMode(){
	Serial.print("Pumping water\n");
	digitalWrite(PUMP_PIN, HIGH);
	delay(10000);
	digitalWrite(PUMP_PIN, LOW);
}

void mesureSoilMoisture_manualMode(){
	digitalWrite(SOIL_MOISTURE_POWER_PIN, HIGH);
	delay(100);
	Serial.print("The soil moisture is: ");
	Serial.print(analogRead(SOIL_MOISTURE_ANALOG_PIN));
	Serial.println();
	delay(100);
	digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
}
