//Input Pin Variables

const int MIC = A0;

//Other Variables

int micReading = 0; // variable to hold mics raw input value
int micVolume = 0; // variable to hold the converted mic volume

//Void Setup - runs once at start

void setup() 
{
   Serial.begin(9600); // Initialise Serial Monitor
}

//Void Loop - repeats forever

void loop() 
{
   int micMin = 1024; // Sets micMin to 1024 before the 50 readings decrease the number
   int micMax = 0; // Sets micMax to 0 before the 50 readings increase the number 

   for (int i = 0; i < 50; ++i) // Perform 50 reads
      {
        int micVal = analogRead(MIC); // Read value from microphone
        micMin = min(micMin, micVal); // Decreases micMin if val is less than it
        micMax = max(micMax, micVal); // Increases micMax if val is more than it
      }

   micReading = micMax - micMin; // Finds the average volume
   micVolume = map(micReading,0,775,0,100); // Maps micReading to a percentage

   Serial.print("Ambient Noise: "); // print text to Serial Monitor
   Serial.print(micVolume); // print variable’s value and start a new line
   Serial.println("%"); // print text to Serial Monitor

   delay(100); // delay for 100 milliseconds
}
