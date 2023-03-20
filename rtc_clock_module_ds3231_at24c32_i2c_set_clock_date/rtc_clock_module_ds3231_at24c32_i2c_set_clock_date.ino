/*

  RTC Clock Module DS3231 AT24C32 I2C (Set clock / date)

  Parts required:
  - Arduino Board
  - RTC Clock Module DS3231 AT24C32 I2C

Libary Required:
  - DS3231 (Included in Source Code)

  Programming by René Rasmussen
  Website : www.it-teknolog.dk
  Contact : renerasmussen@it-teknolog.dk
  Date : 6 Jan 2020
  Version : v1.0

  Modulet kan købes på www.arduinotech.dk

*/

#include <DS3231.h>           // include library 
DS3231 rtc(SDA, SCL);         // create object from DS3231

void setup()
{
  Serial.begin(9600);         // start Serial Monitor
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  rtc.begin();                // start rtc

  rtc.setDOW(FRIDAY);         // Set Day-of-Week to FRIDAY
  rtc.setTime(10, 18, 0);     // Set the time to 10:18:00 (24hr format)
  rtc.setDate(10, 1, 2020);   // Set the date to January 10st, 2020
}

void loop() {
}
