/*
Written by Martyn Evans @ Short Circuits under the MIT License.

This uses the MOTHERBOARD, DIGITISER, SENSOR ARRAY and RGB MATRIX kits. 
Wire up the kits according to the pin assignments under PINS in each of the following sections, 
or change the pin assignments according to your wiring.
Written in easy to understand code, not efficient code.

Functions:

RGB Matrix shows 4 vertical bar graphs representing temperature, humidity, 
sound and light levels read by the various sensors of the Sensor Array.
Time, Date and Year are displayed on the Digitiser. 
Left button cycles the Time, Date and Year, also changing the mode LEDs.
Right button turns both displays off. 
An alarm can be set using alarmtime. When it goes off, a message is displayed.
Set the alarm time and message by changing alarmtime and alarmtext respectively.

To set the time: upload the code without commenting "rtc.adjust..." Then re-comment and re-upload the code. 
If you don't, every time you turn the device off the time will be reset to the time you uploaded the code. 
*/

//RTC Stuff

#include "RTClib.h" // Include RTClib library
RTC_DS1307 rtc; // Create an instance of the DS1307
int alarm = 0; // alarm on or off
int alarmTime = 0100; // set the alarm time here

//Digitiser

//PINS
const int SER = 3;
const int CLK = 4;
const int LATCH = 5;
const int OE = 11;
const int sw1 = A1;
const int sw2 = A0;

int mode = 0; // counter for Mode select
int mode2 = 0; // counter for on/off 
int swState = 0; // State of Button 1
int lastswState = 0; // previous state of Button 1
int sw2State = 0; // State of Button 2
int lastsw2State = 0; // previous state of Button 2

int num = 0;
int thousands = 0;
int hundreds = 0;
int tens = 0;
int ones = 0;

const int digit[4] =
{
  B11111110,B11111101,B11111011,B11110111
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

/*
G F A B C D E  (Segment)
1 2 3 4 6 7 8  (Digit)
5th digit is decimal point
0 is on

a 00001010
b 00111000
c 10011100
d 01101000
e 00011100
f 00011110
g 10011000
h 00111010
i 10111110
j 11101000
k 00011010
l 10111100
m 11011010
n 10001010
o 10001000
p 00001110
q 00001011
r 10001110
s 00011001
t 00111100
u 10101000
v 10101001
w 10101101
x 00101010
y 00101001
z 01001101
*/

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

// Set Alarm Text Here

char alarmtext[] = {xx,xx,xx,g,o,xx,t,o,xx,s,l,e,e,p,xx,xx,xx};

//RGB MATRIX

//PINS
const int RGBSER = 8;
const int RGBCLK = 7;
const int RGBLATCH = 6;
const int RGBOE = 9;

int fade = 0;
int Output1 = 0;
int Output2 = 0;
int Output3 = 0;
int Output4 = 0;
int Output5 = 0;
int Output6 = 0;
int Output7 = 0;
int Output8 = 0;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;

const int temp1[5] =
{
  B00000000, B00000000, B00000000, B00000000, B00000000
};

const int temp2[5]
{
  B11110000, B11101000, B11001000, B10001000, B00001000
};

const int humid1[5] =
{
  B00000000, B00000100, B00000100, B00000100, B00000100
};

const int humid2[5]
{
  B11110000, B11100000, B11000000, B10000000, B00000000
};

const int vol1[5] =
{
  B00000000, B00100000, B00100000, B00100000, B00100000
};

const int vol2[5]
{
  B11110000, B11100000, B11000000, B10000000, B00000000
};

const int light1[5] =
{
  B00000000, B00000001, B00000001, B00000001, B00000001
};

const int light2[5]
{
  B11110000, B11100001, B11000001, B10000001, B00000001
};

// SENSOR ARRAY

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//PINS
#define DHTPIN 13
const int MIC = A3;
const int LIGHT = A2;

#define DHTTYPE    DHT11     // DHT 11
DHT_Unified dht(DHTPIN, DHTTYPE);

int temp = 0;
int newTemp = 0;
int humid = 0;
int newHumid = 0;
int vol = 0;
int newVol = 0;
int light = 0;
int newLight = 0;

void setup() 

{

Serial.begin(9600);

// put your setup code here, to run once:

//RGB MATRIX setup

pinMode(RGBSER, OUTPUT); // RGBSER (data) pin as output
pinMode(RGBCLK, OUTPUT); // RGBCLK (clock) pin as output
pinMode(RGBLATCH, OUTPUT); // RGBLATCH pin as output
pinMode(RGBOE, OUTPUT); // RGBOE pin as output

//RTC Stuff

rtc.begin();

//rtc.adjust(DateTime(__DATE__,__TIME__));; // Set the RTC to Compile Date and Time. Re-comment and re-upload when time is set

//Digitiser

pinMode(SER, OUTPUT); // SER (data) pin as output
pinMode(CLK, OUTPUT); // CLK (clock) pin as output
pinMode(LATCH, OUTPUT); // LATCH pin as output
pinMode(OE, OUTPUT); // OE pin as output

pinMode(sw1, INPUT); // Switch 1
pinMode(sw2, INPUT); // Switch 2
//pinMode(Pot, INPUT); // Potentiometer

//SENSOR ARRAY setup

pinMode(MIC, INPUT);
pinMode(LIGHT, INPUT);

dht.begin();
sensors_event_t event;
dht.temperature().getEvent(&event);
temp = event.temperature;
dht.humidity().getEvent(&event);
humid = event.relative_humidity;
  
}


void rgbshow()
{

//Shift Out RGB Matrix

int d = 0;

digitalWrite(RGBLATCH, LOW);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output1);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output2);
digitalWrite(RGBLATCH,HIGH);

delay(d);

digitalWrite(RGBLATCH, LOW);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output3);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output4);
digitalWrite(RGBLATCH,HIGH);

delay(d);

digitalWrite(RGBLATCH, LOW);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output7);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output8);
digitalWrite(RGBLATCH,HIGH);

delay(d);

digitalWrite(RGBLATCH, LOW);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output5);
shiftOut(RGBSER,RGBCLK,MSBFIRST,Output6);
digitalWrite(RGBLATCH,HIGH);

delay(d);

}

void loop() 
{

// Set Display Fade
if (mode2 == 0)
{
  fade = 0;
}
else 
{
  fade = 255;
}

analogWrite(OE, fade);
analogWrite(RGBOE, fade);

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

    // Delay a bit to avoid bouncing
    delay(10);
  }

// save the current state as the last state, for next time through the loop
lastswState = swState;

if (sw2State != lastsw2State) {
    // if the state has changed, increment the counter
    if (sw2State == HIGH)
    {
      // if the current state is HIGH then the button went from off to on:
      if (mode2 < 1)
      {
        mode2++;
      }
      else
      {
        mode2 = 0;
      }
    }
    // Delay a bit to avoid bouncing
    delay(10);
}

// save the current state as the last state, for next time through the loop
lastsw2State = sw2State;

// Time Stuff

DateTime now = rtc.now();      // get the current time

//Alarm

if (now.hour() * 100 + now.minute() == alarmTime) // If its alarm time, set alarm as 1
{
  alarm = 1;
}
else 
{
alarm = 0;
}

// Alarm Message

if (alarm == 1)
{

// Message:        s  t  r  e t  c h   y  o  u  r    l  e g s
// letter lookup:  19 20 18 5 20 3 8 0 25 15 21 18 0 12 5 7 19

/*
 * Order: 0, 0, 0, 0
 *        0, 0, 0, 19
 *        0, 0, 19,20
 *        0, 19,20,18
 *        19,20,18,5
 *        20,18,5, 20
 *        18,5, 20,3
 *        5,20, 3, 8
 *        
 */

  for (int cha = 0; cha <= sizeof(alarmtext) -1; cha++)
  {
    //Serial.println(letter[alarmtext[cha]]);
    for (int nm = 0; nm <= 40; nm++)
    {

    // Shift Out Message

    int d1 = 1;

    digitalWrite(LATCH, LOW);
    shiftOut(SER,CLK,LSBFIRST,letter[alarmtext[cha]]);
    shiftOut(SER,CLK,LSBFIRST,digit0);
    digitalWrite(LATCH,HIGH);

    delay(d1);

    digitalWrite(LATCH, LOW);
    shiftOut(SER,CLK,LSBFIRST,letter[alarmtext[cha+1]]);
    shiftOut(SER,CLK,LSBFIRST,digit1);
    digitalWrite(LATCH,HIGH);

    delay(d1);

    digitalWrite(LATCH, LOW);
    shiftOut(SER,CLK,LSBFIRST,letter[alarmtext[cha+2]]);
    shiftOut(SER,CLK,LSBFIRST,digit2);
    digitalWrite(LATCH,HIGH);

    delay(d1);

    digitalWrite(LATCH, LOW);
    shiftOut(SER,CLK,LSBFIRST,letter[alarmtext[cha+3]]);
    shiftOut(SER,CLK,LSBFIRST,digit3);
    digitalWrite(LATCH,HIGH);

    delay(d1);

    }

  }

}

if (mode == 0) // Time
  {
    num = (now.hour() * 100 + now.minute());
    digit0 = digit[0] & B10001111;
    digit1 = digit[1] & B10001111;
    digit2 = digit[2] & B10001111;
    digit3 = digit[3] & B10001111;
    //Serial.println(n);
  }

else if (mode == 1) // Day / Month
  {
    num = (now.day() * 100 + now.month());
    digit0 = digit[0] & B01001111;
    digit1 = digit[1] & B01001111;
    digit2 = digit[2] & B01001111;
    digit3 = digit[3] & B01001111;
    //Serial.println(n);
  }

else if (mode == 2) // Year
  {
    num = now.year();    
    digit0 = digit[0] & B00101111;
    digit1 = digit[1] & B00101111;
    digit2 = digit[2] & B00101111;
    digit3 = digit[3] & B00101111;
    //Serial.println(n);
  }

//Serial.println(num);
  
thousands = ((num/1000));      // get the thousands value
hundreds = ((num%1000)/100);   // get the hundreds value
tens = ((num%100)/10);         // get the tens value
ones = ((num%10)/1);           // get the ones value

// Shift Out DIGITISER

int d1 = 3;

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

if (millis() - previousMillis2 > 6000)
  {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    temp = event.temperature;
    dht.humidity().getEvent(&event);
    humid = event.relative_humidity;
    //Serial.print("humid = ");
    //Serial.println(humid);
    //Serial.print("New humidity = ");
    //Serial.println(newHumid);
    //Serial.print("temp = ");
    //Serial.println(temp);
    //Serial.print("New temp = ");
    //Serial.println(newTemp);
    previousMillis2 = millis();    
  }

if (millis() - previousMillis3 > 100)
  {
    light = analogRead(LIGHT);
    previousMillis3 = millis();    

  }

int mn = 1024; // mn only decreases
int mx = 0;    // mx only increases

// Perform 20 reads. Update mn and mx for each one.
for (int ii = 0; ii < 20; ++ii)
  {

    int val = analogRead(MIC);
    mn = min(mn, val);
    mx = max(mx, val);

  }

vol = abs(mx - mn);
newTemp = map(temp,0,40,0,4);
newHumid = map(humid,0,80,0,4);
newVol = map(vol,0,650,0,4);
newLight = map(light,0,700 ,0,4);
Output1 = temp1[newTemp];
Output2 = temp2[newTemp];
Output3 = humid1[newHumid];
Output4 = humid2[newHumid];
Output5 = vol1[newVol];
Output6 = vol2[newVol];
Output7 = light1[newLight];
Output8 = light2[newLight];

rgbshow();

  //Serial.print("vol = ");
  //Serial.println(vol);
  //Serial.print("newVol = ");
  //Serial.println(newVol);
  //Serial.print("Light = ");
  //Serial.println(light);
  //Serial.print("New light = ");
  //Serial.println(newLight);
}
