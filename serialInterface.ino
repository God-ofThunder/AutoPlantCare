#include "serialInterface.h"
#include "tests.h"
#include "automatic.h"

void setSerial(){
	Serial.begin(9600);
	while(!Serial) delay(10);
	Serial.setTimeout(1000);
}

void resetSerial(){
	Serial.end();
	Serial.begin(9600);
}

void printClock(){
	Serial.print("The clock is: ");
	Serial.print(int(clock/(1000*60*60)));
	Serial.print(":");
	Serial.print(int((clock/(1000*60))%60));
	Serial.println();
}

void printIsLightOn(){
	if(lightIsOn == true)
		Serial.print("Light Is On\n");
	else 
		Serial.print("Light Is Not On\n");
}

void printLightOnPeriod(){
	Serial.print("The light turns on kl ");
	Serial.print(int(lightOnTime/(1000*60*60)));
	Serial.print(":");
	Serial.print(int((lightOnTime/(1000*60))%60));
	Serial.println();
	Serial.print("The light turns off kl ");
	Serial.print(int(lightOffTime/(1000*60*60)));
	Serial.print(":");
	Serial.print(int((lightOffTime/(1000*60))%60));
	Serial.println();
}

void printSoilMoisture(){
	Serial.print("not functional yet\n");
}

void printPumpPower(){
	Serial.print("not functional yet\n");
}

int getIntAsIndputFromUser(){
	int indput = 0;
	int timeOut = 0;
	while(indput < 1 && timeOut < 30){
		indput = Serial.parseInt();
		timeOut++;
		delay(1000);
	}
	resetSerial();
	if(indput < 1){
		Serial.print("Error did not get indput in time");
		return 0;
	}
	return indput;
}

struct Time getTimeFromUser(){
	struct Time t;
	Serial.print("Set Time: ");
	t.hours = getIntAsIndputFromUser();
	Serial.println();
	Serial.print("Set Minuts: ");
	t.minuts = getIntAsIndputFromUser();
	Serial.println();
	Serial.print("Set Seconds: ");
	t.seconds = getIntAsIndputFromUser();
	Serial.println();
	return t;
}

bool readyForCommand = false;
void getIndput(){
	if(!Serial)
		return;
	if(readyForCommand == false){
		Serial.print("Enter Command: ");
		readyForCommand = true;
	}
	String command = Serial.readString();
	command.trim();
	resetSerial();
	if(command == ""){
		readyForCommand = true;
		return;
	}
	readyForCommand = false;
	handelCommand(command);
}

void printMode(){
	if(manualMode == true){
		Serial.print("manual mode\n");
		return;
	}
	Serial.print("automatick mode\n");
	return;
}

void printHelp(){
	Serial.print("Info:\n");
	Serial.print("This is an automatick light and water for plants program\n");
	Serial.println();
	Serial.print("The mode is set to ");
	printMode();
	Serial.println();
	Serial.print("Available commands:\n");
	Serial.print("  h(help)\n");
	Serial.print("  c		Shows the clock\n");
	Serial.print("  m		Set to manual mode\n");
	Serial.print("  a		Set to automatick mode\n");
	Serial.println();
	Serial.print("Commands for automatick mode\n");
	Serial.print("  sc		Set the clock to the corect time\n");
	Serial.print("  slont	Set the time to turn on the light\n");
	Serial.print("  slofft	Set the time to turn off the light\n");
	Serial.print("  stmsm	Set the time to automatick mesure soil moisture\n");
	Serial.print("  psm		Prints the last mesured soil moisture\n");
	Serial.print("  plont	Prints the period when the light is on\n");
	Serial.println();
	Serial.print("Commands for manual mode\n");
	Serial.print("  lon		Turn light on\n");
	Serial.print("  loff	Turn light off\n");
	Serial.print("  p		Turn pump on for 10 seconds\n");
	Serial.print("  msm		Mesure soil moisture\n");
}

void handelCommand(String command){
	if(command == "help" || command == "h"){
		Serial.print("Command was h\n");
		printHelp();
	}

	else if(command == "c"){
		Serial.print("Command was c\n");
		printClock();
	}
	
	else if(command == "m"){
		Serial.print("Command was m\n");
		manualMode = true;
	}
	
	else if(command == "a"){
		Serial.print("Command was a\n");
		manualMode = false;
	}
	
	else if(command == "sc"){
		Serial.print("Command was sc\n");
		setClock();
	}
	
	else if(command == "slont"){
		Serial.print("Command was slont\n");
		setLightOnTime();
	}
	
	else if(command == "slofft"){
		Serial.print("Command was slofft\n");
		setLightOffTime();
	}
	
	else if(command == "stmsm"){
		Serial.print("Command was stmsm\n");
		setCheckSoilMoistureTime();
	}
	
	else if(command == "psm"){
		Serial.print("Command was psm\n");
		printSoilMoisture();
	}

	else if(command == "plont"){
		Serial.print("Command was plont\n");
		printLightOnPeriod();
	}

	else if(command == "lon"){
		Serial.print("Command was lon\n");
		turnOnLight_manualMode();
	}

	else if(command == "loff"){
		Serial.print("Command was loff\n");
		turnOffLight_manualMode();
	}

	else if(command == "p"){
		Serial.print("Command was p\n");
		pumpWater_manualMode();
	}

	else if(command == "msm"){
		Serial.print("Command was msm\n");
		mesureSoilMoisture_manualMode();
	}

	else{
		Serial.print("Did not recognise command\n");
	}
}
