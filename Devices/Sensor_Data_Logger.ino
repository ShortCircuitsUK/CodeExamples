/*
Written by Martyn Evans @ Short Circuits under the MIT License.

This uses the MOTHERBOARD, and SENSOR ARRAY kits
Wire the sensor array's DHT pin to pin 9 and the 4 SD card pins to 10, 11, 12 and 13 respectively 
you can change the DHT pin, but the SD card pins are set by libraries

Written in easy to understand code, not efficient code

Functions:

Saves the temperature, humidity, time and date to a text file on the SD card every 5 mins.
*/


//Include Libraries

#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h> // includes Adafruit sensor library
#include <DHT.h> // includes DHT library
#include <DHT_U.h> // includes DHT_U library
#include "RTClib.h" // Include RTClib library
RTC_DS1307 rtc; // Create an instance of the DS1307

//Other Variables

#define DHTPIN 9 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // Indicate the sensor type: DHT11 or DHT22
DHT_Unified dht(DHTPIN, DHTTYPE); // sets the pin and type
File myFile; // Creates a file object called myFile777777

int temp = 0; // variable to hold temperature data
int humid = 0; // variable to hold humidity data

void setup() // Void Setup - runs once at start
{
   Serial.begin(9600); // Initialise Serial Monitor
   Serial.println("Initializing SD card...");
   if (!SD.begin()) 
   {
      Serial.println("initialization failed");
      while (1);
   }
   Serial.println("initialization done");
   dht.begin(); // Initialise DHT Sensor
   rtc.begin();
   //rtc.adjust(DateTime(__DATE__,__TIME__));; // Set the RTC to Compile Date and Time
}

void loop() // Void Loop - repeats forever
{
   sensors_event_t event; // Prepares for the following events
   dht.temperature().getEvent(&event); // Gets the temperature data from the DHT
   temp = event.temperature; // Saves the temperature to a variable
   dht.humidity().getEvent(&event); // Gets the relative humidity data from the DHT
   humid = event.relative_humidity; // Saves the relative humidity to a variable
   DateTime now = rtc.now();      // get the current time
   
   myFile = SD.open("data.txt", FILE_WRITE);
   if (myFile)
   {
      Serial.println("Data saving...");
      Serial.print(temp);
      Serial.print(",");
      Serial.print(humid);
      Serial.print(",");
      Serial.print(now.day());
      Serial.print(".");
      Serial.print(now.month());
      Serial.print(".");
      Serial.print(now.year());
      Serial.print(",");
      Serial.print(now.hour());
      Serial.print(":");
      Serial.println(now.minute());      
      
      myFile.print(temp);
      myFile.print(",");
      myFile.print(humid);
      myFile.print(",");
      myFile.print(now.day());
      myFile.print(".");
      myFile.print(now.month());
      myFile.print(".");
      myFile.print(now.year());
      myFile.print(",");
      myFile.print(now.hour());
      myFile.print(":");
      myFile.println(now.minute());      
      myFile.close();
      Serial.println("Data saved");
   }
   else
   {
      Serial.println("Error writing to file");
   }
   delay(300000); // delay for 5 mins
}
