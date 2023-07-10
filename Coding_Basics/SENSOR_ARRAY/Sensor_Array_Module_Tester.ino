// Short Circuits - Sensor Array - Module Test Script
// Thanks to those who wrote the libraries used in this sketch. Limor Fried, Tom Igoe, Tony DiCola

//  Adding libraries

//DHT

#include <Adafruit_Sensor.h> // includes Adafruit sensor library
#include <DHT.h> // includes DHT library
#include <DHT_U.h> // includes DHT_U library

//SD

#include <SPI.h> // includes SPI library
#include <SD.h> // includes SD library

// Declaring inputs and variables

//DHT11

#define DHTPIN 9     // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 // Indicate the sensor type: DHT11 or DHT22
DHT_Unified dht(DHTPIN, DHTTYPE); // sets the pin and type
int temp = 0; // variable to hold temperature data
int humid = 0; // variable to hold humidity data

//SD

const int chipSelect = 10; // can be any input pin
// MOSI (Dout) - defined in library as pin 11
// MISO (Din) - defined in library as pin 12
// CLK - defined in library as pin 13
Sd2Card card; // SD card library stuff
SdVolume volume; // SD card library stuff
SdFile root; // SD card library stuff

//Microphone

const int Mic = A0; // Sets the Microphone input pin to A0
int micReading = 0; // variable to hold microphone reading

//LDR

const int LDR = A3; // Sets the LDR input pin to A3
int lightReading = 0; // variable to hold LDR reading


void setup() {

Serial.begin(9600); // Initialise Serial Monitor
dht.begin(); // Initialise DHT Sensor

//SD Card test (Insert a FAT32 formatted, 32GB or less Micro SD)

Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed.");
    Serial.println("Things to check:");
    Serial.println("* is a FAT32 card (32GB or less) inserted?");
    Serial.println("* are there any solder bridges on the SD card slot?");
    Serial.println("* did you change the chipSelect (CS) pin to match your wiring?");
    Serial.println(" ");
  } else {
    Serial.println("SD Card slot working correctly and a card is present.");
    Serial.println(" ");
  }

}

void loop() {

sensors_event_t event; // Prepares for the following events

dht.temperature().getEvent(&event); // Gets the temperature data from the DHT
temp = event.temperature; // Saves the temperature to a variable
Serial.print("Temperature: "); // Print to serial monitor
Serial.print(temp); // Print the temperature to serial monitor
Serial.println(" "); // Inserts an empty line and a space

dht.humidity().getEvent(&event); // Gets the relative humidity data from the DHT
humid = event.relative_humidity; // Saves the rh to a variable
Serial.print("Relative Humidity: "); // Print text to serial monitor
Serial.print(humid); // Print the rh to serial monitor
Serial.println(" "); // Inserts an empty line and a space

micReading = analogRead(Mic); // Saves the reading from the analog pin to a variable
Serial.print("Microphone Reading: "); // Print text to serial monitor
Serial.print(micReading); // Print the mic reading to serial monitor
Serial.println(" "); // Inserts an empty line and a space

lightReading = analogRead(LDR);  // Saves the reading from the analog pin to a variable
Serial.print("LDR Reading: "); // Print text to serial monitor
Serial.println(lightReading); // Print the light reading to serial monitor
Serial.println(" "); // Inserts an empty line and a space

delay(5000); // Delay for 5 seconds

}
