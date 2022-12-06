/*
Written by Martyn Evans @ Short Circuits under the MIT License.

This uses the MOTHERBOARD, DIGITISER and SENSOR ARRAY kits
Wire up the kits according to the pin assignments under PINS in each of the following sections
or change the pin assignments according to your wiring
Written in easy to understand code, not efficient code

Functions:

Digitiser shows temperature and humidity
Switching between the two every 5 seconds
To set the delay, change delay1 and delay2
*/

//PINS
const int SER = 7;    // Shift Register Serial Data pin
const int CLK = 8;    // Shift Register Clock pin
const int LAT = 9;    // Shift Register Latch pin
const int OE = 10;    // Shift Register Output Enable pin
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

//Digitiser Stuff

int num = 0;
int thousands = 0;
int hundreds = 0;
int tens = 0;
int ones = 0;

const int digit[4] =
{
  B00001110,B00001101,B00001011,B00000111
};

int digit0 = digit[0];
int digit1 = digit[1];
int digit2 = digit[2];
int digit3 = digit[3];

const int number[10] =
{
  B10001000,B11101011,B01001100,B01001001,B00101011,B00011001,B00111000,B11001011,B00001000,B00001011
};

// Sensor Variables and libraries

unsigned long LastRead = 0;
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE);

// Delay Variables

int delay1 = 5000;
int delay2 = 10000;
unsigned long previousMillis = 0;

//Void Setup - runs once at start

void setup() 
{
    pinMode(OE, OUTPUT); 
    pinMode(SER, OUTPUT); 
    pinMode(CLK, OUTPUT); 
    pinMode(LAT, OUTPUT); 

    analogWrite(OE, 0);

    dht.begin(); // Initialise DHT Sensor
}

void loop() 
{

unsigned long currentMillis = millis();

if (currentMillis - previousMillis <= delay1) 
  {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    num = event.temperature;
    digit0 = digit[0] | B00010000;
  }

if (currentMillis - previousMillis >= delay1 && currentMillis - previousMillis <= delay2)
  {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    num = event.relative_humidity;
    digit0 = digit[0] | B10000000;
  }  

if (currentMillis - previousMillis >= delay2)
{
  previousMillis = currentMillis;
}
    
thousands = ((num/1000));      // get the thousands value
hundreds = ((num%1000)/100);   // get the hundreds value
tens = ((num%100)/10);         // get the tens value
ones = ((num%10)/1);           // get the ones value

// Shift Out DIGITISER

int d1 = 2;

digitalWrite(LAT, LOW);
shiftOut(SER,CLK,LSBFIRST,number[thousands]);
shiftOut(SER,CLK,LSBFIRST,digit0);
digitalWrite(LAT,HIGH);

delay(d1);

digitalWrite(LAT, LOW);
shiftOut(SER,CLK,LSBFIRST,number[hundreds]);
shiftOut(SER,CLK,LSBFIRST,digit1);
digitalWrite(LAT,HIGH);

delay(d1);

digitalWrite(LAT, LOW);
shiftOut(SER,CLK,LSBFIRST,number[tens]);
shiftOut(SER,CLK,LSBFIRST,digit2);
digitalWrite(LAT,HIGH);

delay(d1);

digitalWrite(LAT, LOW);
shiftOut(SER,CLK,LSBFIRST,number[ones]);
shiftOut(SER,CLK,LSBFIRST,digit3);
digitalWrite(LAT,HIGH);

delay(d1);

}
