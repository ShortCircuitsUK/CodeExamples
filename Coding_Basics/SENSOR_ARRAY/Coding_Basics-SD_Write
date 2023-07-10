//Include Libraries

#include <SPI.h> // Include the SPI communication library
#include <SD.h> // Include the SD library

//Variables

int data1 = 0; // First variable we want to save to SD
int data2 = 0; // Second variable we want to save to SD

File myFile; // Creates a file object called myFile

void setup() // Void Setup - runs once at start
{
   Serial.begin(9600); // Initialise Serial Monitor
   Serial.print("Initialising SD card..."); // Print text to serial monitor
   if (!SD.begin()) // if statement that checks if an SD card is NOT present
   {
      Serial.println("initialisation failed!"); // If not present then print text to serial monitor
      while (1); // Wait while this is true
   }
   Serial.println("initialisation done."); // If there IS a card then print this text and move on
}

void loop() // Void Loop - repeats forever
{
   myFile = SD.open("data.txt", FILE_WRITE); // Open or create file with write permissions
   if (myFile) // if the file is open...
   {
      Serial.println("Data saving..."); // Inform user that the program is saving data to SD
      myFile.print(data1); // Write first variable to SD
      myFile.print(","); // Write a comma after the first piece of data
      myFile.println(data2); // Write the second piece of data
      myFile.close(); // Close the file to ensure data is saved
      Serial.println("Data saved"); // Inform the user that the data is saved 
   }
   else // if the file isn’t open...
   {
      Serial.println("Error writing to file"); // Inform the user that there was an error
   }
   delay(300000); // Delay for 5 mins 
}
