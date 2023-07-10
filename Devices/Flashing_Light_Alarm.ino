/*
Written by Martyn Evans @ Short Circuits under the MIT License.

This uses the MOTHERBOARD, and RGB MATRIX kits
Wire up the kits according to the pin assignments under PINS
or change the pin assignments according to your wiring
Written in easy to understand code, not efficient code

Functions:

RGB MATRIX flashes green at a set time
Modify timeHour and timeMinute on line 74 to set the alarm time
Change the Byte values and timing to change the visuals
*/

//RTC Stuff

#include "RTClib.h"
RTC_DS1307 rtc;

//RGB MATRIX Stuff

//PINS

const int SER = 3;
const int CLK = 4;
const int LAT = 5;
const int OE = 6;

int timeHour = 0;
int timeMinute = 0;
int timeNow = 0;

void setup() {

// Start Serial Comminication

Serial.begin(9600);

//RTC Stuff

rtc.begin();

//rtc.adjust(DateTime(__DATE__,__TIME__));; // Set the RTC to Compile Date and Time

//RGB MATRIX Stuff

pinMode(SER, OUTPUT); // sr SER(data) pin as output
pinMode(CLK, OUTPUT); // sr CLK (clock) pin as output
pinMode(LAT, OUTPUT); // sr LATCH pin as output
pinMode(OE, OUTPUT); // sr LATCH pin as output

analogWrite(OE,0); // set brightness to full

//Set all outputs to off

digitalWrite(LAT, LOW); //stops outputs changing
shiftOut(SER,CLK,MSBFIRST,00000000); //all green columns off, all blue columns off
shiftOut(SER,CLK,MSBFIRST,11110000); //all rows off, all red columns off
digitalWrite(LAT,HIGH); //sends changes to outputs

}

void loop() {

DateTime now = rtc.now(); // get the current time

timeMinute = now.minute(); //save the current minute to a variable
timeHour = now.hour(); //save the current hour to a variable

Serial.println(timeHour); //print hour to serial monitor for testing
Serial.println(timeMinute); //print miutes to serial monitor for testing 

if (timeHour == 17 && timeMinute == 30) //if it is 1700 hours and 30 minutes, run the code below
{
  
  digitalWrite(LAT,LOW); //stops outputs changing
  shiftOut(SER,CLK,MSBFIRST,B11110000); //all green columns on, all blue columns off
  shiftOut(SER,CLK,MSBFIRST,B00000000); //all rows on, all red columns off
  digitalWrite(LAT,HIGH); //sends changes to outputs

  delay(500); //delay 500 milliseconds
  
  digitalWrite(LAT,LOW); //stops outputs changing
  shiftOut(SER,CLK,MSBFIRST,00000000); //all green columns off, all blue columns off
  shiftOut(SER,CLK,MSBFIRST,11110000); //all rows off, all red columns off
  digitalWrite(LAT,HIGH); //sends changes to outputs

  delay(500); //delay 500 milliseconds

}

}
