// the relay for controling the power source is contoled by pin 27
#define POWER_PIN (16)
#define SOIL_MOISTURE_ANALOG_PIN (A0)
#define SOIL_MOISTURE_DIGITAL_PIN (11)
#define SOIL_MOISTURE_POWER_PIN (7)
#define BATTERY_LEVEL_BORD_PIN (A7)
#define BATTERY_LEVEL_PUMP_PIN (A6)
#define PUMP_PIN (A2)

int timeOfDayInMillis;
int lightOnMillis;
int lightOffMillis;
int pumpOnMillis;
int startTime;
int maxMillis;

int calculateTimeToMillis(int hour, int minute, int second)
{
	return ((hour*60+minute)*60+second)*1000;
}

void setup()
{
	Serial.begin(9600);
	pinMode(POWER_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_POWER_PIN, OUTPUT);
	pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT);
	pinMode(SOIL_MOISTURE_ANALOG_PIN, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);
	digitalWrite(PUMP_PIN, LOW);
	digitalWrite(POWER_PIN, LOW);
	
	int hourWhenCompiled = 3;
	int minuteWhenCompiled = 59;
	int secondWhenCompiled = 0;
	int lightOnHour = 4;
	int lightOnMinute = 0;
	int lightOffHour = 20;
	int lightOffMinute = 0;
	int pumpOnHour = 5;
	int pumpOnMinute = 30;

	timeOfDayInMillis = calculateTimeToMillis(hourWhenCompiled, minuteWhenCompiled, secondWhenCompiled);
	lightOnMillis = calculateTimeToMillis(lightOnHour, lightOnMinute, 0);
	lightOffMillis = calculateTimeToMillis(lightOffHour, lightOffMinute, 0);
	pumpOnMillis = calculateTimeToMillis(pumpOnHour, pumpOnMinute, 0);
	maxMillis = calculateTimeToMillis(24, 0, 0);
}

/*void printSoilMoisture()
{
	digitalWrite(SOIL_MOISTURE_POWER_PIN, HIGH);
	delay(100);
	int soilMoistureDigital = digitalRead(SOIL_MOISTURE_DIGITAL_PIN);
	int soilMoistureAnalog = analogRead(SOIL_MOISTURE_ANALOG_PIN);
	digitalWrite(SOIL_MOISTURE_POWER_PIN, LOW);

	Serial.print("The Soil Moiture is: ");
	Serial.print(soilMoistureAnalog);
	Serial.print(", ");
	Serial.print(soilMoistureDigital);
}*/

void power()
{
	if(timeOfDayInMillis > lightOnMillis && timeOfDayInMillis < lightOffMillis)
		digitalWrite(POWER_PIN, LOW);
	else
		digitalWrite(POWER_PIN, HIGH);
}

void soilMoisture()
{
	if(timeOfDayInMillis > pumpOnMillis && timeOfDayInMillis < pumpOnMillis+30000)
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
	while(digitalRead(SOIL_MOISTURE_DIGITAL_PIN) == LOW || timeOut == 30)
	{
		digitalWrite(PUMP_PIN, HIGH);
		timeOut += 1;
		delay(1000);
	}
	digitalWrite(PUMP_PIN, LOW);
}

void loop()
{
	startTime = millis();
	delay(1000);
	Serial.print("Time ");
	Serial.print(int(timeOfDayInMillis/(1000*60*60)));
	Serial.print(":");
	Serial.print(int((timeOfDayInMillis/(1000*60))%60));
	Serial.println();
	// turns power on ore off
	power();
	soilMoisture();
	if(timeOfDayInMillis > maxMillis)
		timeOfDayInMillis -= maxMillis;
	timeOfDayInMillis += millis()-startTime;

}
