const int SER = 3;
const int CLK = 4;
const int LAT = 5;
const int OE = 6;

void setup() 
{
  pinMode(SER, OUTPUT); // SER (data) pin as output
  pinMode(CLK, OUTPUT); // CLK (clock) pin as output
  pinMode(LAT, OUTPUT); // LATCH pin as output
  pinMode(OE, OUTPUT); // Output Enable

  analogWrite(OE,0);
}

void loop() 
{
 for (int i = 0; i < 50; i++)
  {
    digitalWrite(LAT,LOW);
    shiftOut(SER,CLK,MSBFIRST,B00001001);
    shiftOut(SER,CLK,MSBFIRST,B01110110);
    digitalWrite(LAT,HIGH);
    delay(2);

    digitalWrite(LAT,LOW);
    shiftOut(SER,CLK,MSBFIRST,B00000110);
    shiftOut(SER,CLK,MSBFIRST,B10111001);
    digitalWrite(LAT,HIGH);
    delay(2);

    digitalWrite(LAT,LOW);
    shiftOut(SER,CLK,MSBFIRST,B00000110);
    shiftOut(SER,CLK,MSBFIRST,B11011001);
    digitalWrite(LAT,HIGH);
    delay(2);

    digitalWrite(LAT,LOW);
    shiftOut(SER,CLK,MSBFIRST,B00001001);
    shiftOut(SER,CLK,MSBFIRST,B11100110);
    digitalWrite(LAT,HIGH);
    delay(2);
 }

  for (int i = 0; i < 50; i++)
    {
      digitalWrite(LAT,LOW);
      shiftOut(SER,CLK,MSBFIRST,B00000110);
      shiftOut(SER,CLK,MSBFIRST,B01111001);
      digitalWrite(LAT,HIGH);

      delay(2); 

      digitalWrite(LAT,LOW);
      shiftOut(SER,CLK,MSBFIRST,B00001001);
      shiftOut(SER,CLK,MSBFIRST,B10110110);
      digitalWrite(LAT,HIGH);

      delay(2);

      digitalWrite(LAT,LOW);
      shiftOut(SER,CLK,MSBFIRST,B00001001);
      shiftOut(SER,CLK,MSBFIRST,B11010110);
      digitalWrite(LAT,HIGH);

      delay(2);

      digitalWrite(LAT,LOW);
      shiftOut(SER,CLK,MSBFIRST,B00000110);
      shiftOut(SER,CLK,MSBFIRST,B11101001);
      digitalWrite(LAT,HIGH);
   
      delay(2);
    }
}
