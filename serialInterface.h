#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H
bool manualMode = false;
void setSerial();
void resetSerial();
void printClock();
void printIsLightOn();
void printLightOnPeriod();
void printIsPumpOn();
int getIntIndputFromUser();
struct Time getTimeFromUser();
void getIndput();
void printMode();
void printHelp();
void handelCommand(String command);
#endif
