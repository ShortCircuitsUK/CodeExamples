//Adding Libraries 

#include <Adafruit_Sensor.h> // includes Adafruit sensor library
#include <DHT.h> // includes DHT library
#include <DHT_U.h> // includes DHT_U library

//Input Pin Variables

#define DHTPIN 9 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // Indicate the sensor type: DHT11 or DHT22
DHT_Unified dht(DHTPIN, DHTTYPE); // sets the pin and type

//Other Variables

int temp = 0; // variable to hold temperature data
int humid = 0; // variable to hold humidity data

//Void Setup - runs once at start

void setup() 
{
   Serial.begin(9600); // Initialise Serial Monitor
   dht.begin(); // Initialise DHT Sensor
}

//Void Loop - repeats forever

void loop() 
{
   sensors_event_t event; // Prepares for the following events
   dht.temperature().getEvent(&event); // Gets the temperature data from the DHT
   temp = event.temperature; // Saves the temperature to a variable
   dht.humidity().getEvent(&event); // Gets the relative humidity data from the DHT
   humid = event.relative_humidity; // Saves the relative humidity to a variable

   Serial.print("Temp: "); // print text to Serial Monitor
   Serial.println(temp); // print variable’s value and start a new line
   Serial.print("R.Humidity: "); // print text 
   Serial.println(humid); // print variable’s value and start a new line

   delay(5000); // delay for 5 seconds
}
