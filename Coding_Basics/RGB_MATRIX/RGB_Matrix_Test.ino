const int SER = 3;
const int CLK = 4;
const int LAT = 5;
const int OE = 6;

void setup() {
  
pinMode(SER, OUTPUT); // SER (data) pin as output
pinMode(CLK, OUTPUT); // CLK (clock) pin as output
pinMode(LAT, OUTPUT); // LATCH pin as output
pinMode(OE, OUTPUT); // Output Enable

analogWrite(OE,0);

}

void loop() {

//MSBFIRST LED Order:
//B Green1, Green2, Green3, Green4, Blue1, Blue2, Blue3, Blue4 
//B Row1,   Row2,   Row3,   Row4,   Red1,  Red2,  Red3,  Red4

digitalWrite(LAT,LOW);
shiftOut(SER,CLK,MSBFIRST,B00000000); 
shiftOut(SER,CLK,MSBFIRST,B00001111);
digitalWrite(LAT,HIGH);

for (int i=0; i<255; i++)
{
  analogWrite(OE,i);
  delay(10);
}

digitalWrite(LAT,LOW);
shiftOut(SER,CLK,MSBFIRST,B11110000); 
shiftOut(SER,CLK,MSBFIRST,B00000000);
digitalWrite(LAT,HIGH);

for (int i=0; i<255; i++)
{
  analogWrite(OE,i);
  delay(10);
}

digitalWrite(LAT,LOW);
shiftOut(SER,CLK,MSBFIRST,B00001111); 
shiftOut(SER,CLK,MSBFIRST,B00000000);
digitalWrite(LAT,HIGH);

for (int i=0; i<255; i++)
{
  analogWrite(OE,i);
  delay(10);
}

}
