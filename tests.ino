// Manual mode
void turnOnLight_manualMode(){
	digitalWrite(LIGHT_POWER_PIN, LOW);
}

void turnOffLight_manualMode(){
	digitalWrite(LIGHT_POWER_PIN, HIGH);
}

void pumpWater_manualMode(){
	digitalWrite(PUMP_PIN, HIGH);
	delay(10000);
	digitalWrite(PUMP_PIN, LOW);
}

void mesureSoilMoisture_manualMode(){
	digitalWrite(SOIL_MOISTURE_POWER_PIN, HIGH);
	delay(100);
	analogRead(SOIL_MOISTURE_ANALOG_PIN);
}
