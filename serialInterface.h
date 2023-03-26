#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H
bool manualMode = false;
void setSerial();
void resetSerial();
void printClock();
void printIsLightOn();
void printIsPumpOn();
int getIntIndputFromUser();
int* getTimeFromUser();
void getIndput();
void printHelp();
void handelCommand(String command);
#endif
