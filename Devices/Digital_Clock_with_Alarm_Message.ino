/*
Written by Martyn Evans @ Short Circuits under the MIT License.

This uses the MOTHERBOARD, and DIGITISER kits
Wire up the kits according to the pin assignments under PINS in each of the following sections
or change the pin assignments according to your wiring
Written in easy to understand code, not efficient code

Functions:

Digitiser shows time, date, or year
Switch between time, date and year by pressing the left button
A message will display at a set time
*/

//RTC Stuff

#include "RTClib.h" // Include RTClib library
RTC_DS1307 rtc; // Create an instance of the DS1307

//DIGITISER Stuff

//PINS

const int SER = 3;
const int CLK = 4;
const int LATCH = 5;
const int OE = 10;

const int sw1 = A0;
const int Pot = A1;
const int sw2 = A2;


int mode = 0; // counter for Mode select
int swState = 0; // State of Button 1
int lastswState = 0; // previous state of Button 1
int sw2State = 0; // State of Button 2
int lastsw2State = 0; // previous state of Button 2
int potRead = 0;
int potDimVal = 0;

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


const int letter[27] =
{
  B11111111, B00001010,B00111000,B10011100,B01101000,B00011100,B00011110,B10011000,B00111010,B10111110,B11101000,B00011010,B10111100,B11011010,B10001010,B10001000,B00001110,B00001011,B10001110,B00011001,B00111100,B10101000,B10101001,B10101101,B00101010,B00101001,B01001101
};

const int xx = 0;
const int a = 1;
const int b = 2;
const int c = 3;
const int d = 4;
const int e = 5;
const int f = 6;
const int g = 7;
const int h = 8;
const int i = 9;
const int j = 10;
const int k = 11;
const int l = 12;
const int m = 13;
const int n = 14;
const int o = 15;
const int p = 16;
const int q = 17;
const int r = 18;
const int s = 19;
const int t = 20;
const int u = 21;
const int v = 22;
const int w = 23;
const int x = 24;
const int y = 25;
const int z = 26;

//char text[] = {xx,xx,xx,s,t,r,e,t,c,h,xx,y,o,u,r,xx,l,e,g,s,xx,xx,xx};
char text[] = {xx,xx,xx,g,e,t,xx,r,e,a,d,y,xx,f,o,r,xx,d,i,n,n,e,r,xx,xx,xx};

void setup() {

// Start Serial Comminication

Serial.begin(9600);

//RTC Stuff

rtc.begin();

//To set the time on the RTC to match your computer's clock, uncomment the next line and upload the code. To prevent it resetting to the same time every time you reset the device, add the "//" to the beginning of the line then uplaod the code again. The time will then be set and saved even after a reset (with a coin cell present). 

//rtc.adjust(DateTime(__DATE__,__TIME__));; // Set the RTC to Compile Date and Time

//DIGITISER Stuff

pinMode(SER, OUTPUT); // SER (data) pin as output
pinMode(CLK, OUTPUT); // CLK (clock) pin as output
pinMode(LATCH, OUTPUT); // LATCH pin as output
pinMode(OE, OUTPUT); // Output Enable

analogWrite(OE, 150); // Set brightness

pinMode(sw1, INPUT); // Switch 1
pinMode(sw2, INPUT); // Switch 2
pinMode(Pot, INPUT); // Potentiometer

}

void loop() {

// Button state / mode changer

// read the pushbutton input pin:
swState = digitalRead(sw1);
sw2State = digitalRead(sw2);

// compare the swState to its previous state
if (swState != lastswState) {
    // if the state has changed, increment the counter
    if (swState == HIGH)
    {
      // if the current state is HIGH then the button went from off to on:
      if (mode < 2)
      {
        mode++;
      }
      else
      {
        mode = 0;
      }
      //Serial.print("number of button pushes: ");
      //Serial.println(mode);
    }

    // Delay a little bit to avoid bouncing
    //delay(10);
  }

// save the current state as the last state, for next time through the loop
lastswState = swState;

//Alarm
//Change alarmNum to change the alarm time. 
//Change char text[] on line 82 to change the message

DateTime now = rtc.now();      // get the current time

num = (now.hour() * 100 + now.minute());
Serial.println(num);

int alarmNum = 1845; 

if (num == alarmNum)
{
  
// Shift Out DIGITISER

for (int cha = 0; cha <= sizeof(text) -1; cha++)
{

//Serial.println(letter[text[cha]]);

for (int nm = 0; nm <= 40; nm++)

{
 
int d1 = 2;

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,letter[text[cha]]);
shiftOut(SER,CLK,LSBFIRST,digit0);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,letter[text[cha+1]]);
shiftOut(SER,CLK,LSBFIRST,digit1);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,letter[text[cha+2]]);
shiftOut(SER,CLK,LSBFIRST,digit2);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,letter[text[cha+3]]);
shiftOut(SER,CLK,LSBFIRST,digit3);
digitalWrite(LATCH,HIGH);

delay(d1);

}

}

}


else 

{

if (mode == 0) // Time
  {
    num = (now.hour() * 100 + now.minute());
    digit0 = digit[0] | B10000000;

    //Serial.println(n);
  }

else if (mode == 1) // Day / Month
  {
    num = (now.day() * 100 + now.month());
    digit0 = digit[0] | B01000000;

    //Serial.println(n);
  }

else if (mode == 2) // Year
  {
    num = now.year();    
    digit0 = digit[0] | B00100000;

    //Serial.println(n);
  }

//Serial.println(num);
  
thousands = ((num/1000));      // get the thousands value
hundreds = ((num%1000)/100);   // get the hundreds value
tens = ((num%100)/10);         // get the tens value
ones = ((num%10)/1);           // get the ones value

// Shift Out DIGITISER

int potRead = analogRead(Pot);
int potDimVal = map(potRead,0,1020,255,0);
analogWrite(OE,potDimVal); // Set brightness

int d1 = 2;

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,number[thousands]);
shiftOut(SER,CLK,LSBFIRST,digit0);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,number[hundreds]);
shiftOut(SER,CLK,LSBFIRST,digit1);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,number[tens]);
shiftOut(SER,CLK,LSBFIRST,digit2);
digitalWrite(LATCH,HIGH);

delay(d1);

digitalWrite(LATCH, LOW);
shiftOut(SER,CLK,LSBFIRST,number[ones]);
shiftOut(SER,CLK,LSBFIRST,digit3);
digitalWrite(LATCH,HIGH);

delay(d1);

}

}
