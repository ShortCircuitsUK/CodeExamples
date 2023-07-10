//Output Pin Variables 

const int SER = 7;    // Shift Register Serial Data pin
const int CLK = 8;    // Shift Register Clock pin
const int LAT = 9;    // Shift Register Latch pin
const int OE = 10;    // Shift Register Output Enable pin

//Input Pin Variables

const int sw1 = A0;    // Switch 1 pin
const int Pot = A1;    // Potentiometer pin (must be analog pin)
const int sw2 = A2;    // Switch 2 pin

//Other Variables

int mode = 1;     // counter for Mode select
int swState = 0;     // Holds the current state of the switch
int lastswState = 0;     // Holds the previous state of the switch
int potRead = 0;     // Holds the current potentiometer value (0-1024)
int potDimVal = 0;     // Holds the converted dimming value for output to OE (0-255)

//Void Setup - runs once at start

void setup() 
{
    pinMode(OE, OUTPUT); 
    pinMode(SER, OUTPUT); 
    pinMode(CLK, OUTPUT); 
    pinMode(LAT, OUTPUT); 

    analogWrite(OE, 0);
}

//Void Loop - repeats forever

void loop() 
{

//DIM DISPLAY USING POTENTIOMETER

potRead = analogRead(Pot); // Reads the pot and assigns potRead the same value
potDimVal = map(potRead,0,1023,255,0); // maps potRead (0-1023) to potDimVal (255-0)
analogWrite(OE,potDimVal);   // Sets a PWM value (potDimVal) to the OE pin to set brightness

//MODE SWITCHING

swState = digitalRead(sw1);   //read the pushbutton input pin

if (swState != lastswState)   // compare swState to its previous state, if it changed...
    {
    if (swState == HIGH)   // ...and the current state is HIGH then the button was pressed
       {
           if (mode < 4)   // if mode is less than the number of modes
           {
              mode++;   // add 1 to mode, thus changing to the next mode
           }
           else   // if mode is not less than the number of modes...
           {
              mode = 1;   // ...set mode to 0 (the first mode)
           }
       }
       delay(5);   // Delay a little bit to avoid bouncing
    }

lastswState = swState;   // save the current state as the last state

//Shift Out Digits

if (mode == 1) // if mode is equal to 1 then execute the following code
    {
        digitalWrite(LAT,LOW); // sets the latch low
        shiftOut(SER,CLK,LSBFIRST,B11101011); // shifts each bit in the given byte to the serial pin, sending the least significant (right most) bit first
        shiftOut(SER,CLK,LSBFIRST,B10001110); // shifts another byte which pushes the last through to the second register
        digitalWrite(LAT,HIGH); // sets the latch high
    }

if (mode == 2)
    {
        digitalWrite(LAT,LOW);
        shiftOut(SER,CLK,LSBFIRST,B01001100);
        shiftOut(SER,CLK,LSBFIRST,B01001101);
        digitalWrite(LAT,HIGH);
    }

if (mode == 3)
    {
        digitalWrite(LAT,LOW);
        shiftOut(SER,CLK,LSBFIRST,B01001001);
        shiftOut(SER,CLK,LSBFIRST,B00101011);
        digitalWrite(LAT,HIGH);
    }

if (mode == 4)
    {
        digitalWrite(LAT,LOW);
        shiftOut(SER,CLK,LSBFIRST,B00101011);
        shiftOut(SER,CLK,LSBFIRST,B00010111);
        digitalWrite(LAT,HIGH);
    } 
}
