//Input Pin Variables

const int LDR = A3;

//Other Variables

int light = 0; // variable to hold light level reading
int lightLevel = 0; // variable to hold mapped light level

//Void Setup - runs once at start

void setup() 
{
   Serial.begin(9600); // Initialise Serial Monitor
   pinMode(LDR,INPUT); // Declaring the LDR pin as an input
}

//Void Loop - repeats forever

void loop() 
{
   light = analogRead(LDR); // save current LDR value to variable
   Serial.print("Light: "); // print text to Serial Monitor
   lightLevel = map(light,200,1006,0,100); // maps reading to 0-100
   Serial.println(lightLevel); // print variable’s value and start a new line
   delay(1000); // delay for 1 seconds
}
