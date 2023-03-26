#include "serialInterface.h"
#include "mainProgram.h"

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
	Serial.print("not functional yet\n");
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

int* getTimeFromUser(){
	Serial.print("Set Time: ");
	int hours = getIntAsIndputFromUser();
	Serial.println();
	Serial.print("Set Minuts: ");
	int minuts = getIntAsIndputFromUser();
	Serial.println();
	Serial.print("Set Seconds: ");
	int seconds = getIntAsIndputFromUser();
	Serial.println();
	static int time[3] = {hours, minuts, seconds};
	return time;
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
	Serial.print("\n");
	handelCommand(command);
}

void printHelp(){
	Serial.print("Info:\n");
	Serial.print("This is an automatick light and water for plants program\n");
	Serial.println();
	Serial.print("Available commands:\n");
	Serial.print("  h(help)\n");
	Serial.print("  c		Shows the clock\n");
	Serial.print("  sc		Set the clock to the corect time\n");
	Serial.print("  slont	Set the time to turn on the light\n");
	Serial.print("  slofft	Set the time to turn off the light\n");
	Serial.print("  stmsm	Set the time to automatick mesure soil moisture\n");
	Serial.print("  ssm		Shows the last mesured soil moisture\n");
	Serial.print("  m		Set to manual mode\n");
	Serial.print("  a		Set to automatick mode\n");
}

void handelCommand(String command){
	if(command == "help" || command == "h")
		printHelp();
	else if(command == "c")
		printClock();
	else if(command == "sc")
		setClock();
	else if(command == "slont")
		setLightOnTime();
	else if(command == "slofft")
		setLightOffTime();
	else if(command == "stmsm")
		setCheckSoilMoistureTime();
	else if(command == "ssm")
		printSoilMoisture();
	else if(command == "m")
		manualMode = true;
	else if(command = "a")
		manualMode = false;
}
