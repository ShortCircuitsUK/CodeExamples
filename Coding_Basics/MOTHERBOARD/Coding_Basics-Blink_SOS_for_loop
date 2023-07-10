// declaring 3 variables

const int LED = 13; // defines LED as the integer 13 
int i = 0; // defines i as an integer
int j = 0; // defines j as an integer

void setup() 
{

  pinMode(LED,OUTPUT); // sets the pin mode of LED (13) as an output

}

void loop() 
{  
  i=0; // resets i to 0
  
  for (i=0; i<3; i++) // increments i and initiates the code each time until i is no longer less than 3
  {
    digitalWrite(LED,HIGH); // set pin 13 high
    delay(300); // wait for half a second
    digitalWrite(LED,LOW); // set pin 13 low
    delay(1000); // wait for a second
  }
  
  j=0; // resets j to 0
  
  for (j=0; j<3; j++) // increments j and initiates the code each time until j is no longer less than 3
  {
    digitalWrite(LED,HIGH); // set pin 13 high
    delay(1000); // wait for a second
    digitalWrite(LED,LOW); // set pin 13 low
    delay(1000); // wait for a second
  }
}
