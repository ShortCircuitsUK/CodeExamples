// Short Circuits - Sensor Array - Module Test Script
// Thanks to those who wrote the libraries used in this sketch. Limor Fried, Tom Igoe, Tony DiCola
// Upload the code with the Sensor Array wired to the Motherboard according to the pin assignments
// Open the serial plotter in the Arduino IDE to see a live graph of all the sensors

// Adding libraries

//DHT

#include <Adafruit_Sensor.h> // includes Adafruit sensor library
#include <DHT.h> // includes DHT library
#include <DHT_U.h> // includes DHT_U library

// Declaring inputs and variables

//DHT11

#define DHTPIN 9     // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 // Indicate the sensor type: DHT11 or DHT22
DHT_Unified dht(DHTPIN, DHTTYPE); // sets the pin and type
int temp = 0; // variable to hold temperature data
int humid = 0; // variable to hold humidity data

//Microphone

const int Mic = A0; // Sets the Microphone input pin to A0
int micReading = 0; // variable to hold microphone reading

//LDR

const int LDR = A3; // Sets the LDR input pin to A3
int lightReading = 0; // variable to hold LDR reading


void setup() {

Serial.begin(9600); // Initialise Serial Monitor
dht.begin(); // Initialise DHT Sensor

}

void loop() {

sensors_event_t event; // Prepares for the following events

dht.temperature().getEvent(&event); // Gets the temperature data from the DHT
temp = event.temperature; // Saves the temperature to a variable

Serial.print(temp); // Print the temperature to serial monitor
Serial.print(" "); // Inserts an empty line and a space

dht.humidity().getEvent(&event); // Gets the relative humidity data from the DHT
humid = event.relative_humidity; // Saves the rh to a variable

Serial.print(humid); // Print the rh to serial monitor
Serial.print(" "); // Inserts an empty line and a space

micReading = analogRead(Mic); // Saves the reading from the analog pin to a variable

Serial.print(micReading); // Print the mic reading to serial monitor
Serial.print(" "); // Inserts an empty line and a space

lightReading = analogRead(LDR);  // Saves the reading from the analog pin to a variable

Serial.println(lightReading); // Print the light reading to serial monitor

}
