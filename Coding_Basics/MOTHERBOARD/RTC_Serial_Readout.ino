//RTC Stuff

#include "RTClib.h" // Include RTClib library
RTC_DS1307 rtc; // Create an instance of the DS1307
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() // runs once on startup
{

Serial.begin(9600); // Start Serial Comminication

//RTC Stuff

rtc.begin(); // Initiates the RTC

rtc.adjust(DateTime(__DATE__,__TIME__));; // Uses the computer's clock to set the RTCs Date and Time

}

void loop() // repeats

{

DateTime now = rtc.now(); // get the current time

Serial.print("The time is: "); // print "The time is: " to the serial monitor
Serial.print(now.hour()); // print the current hour to the serial monitor
Serial.print(":"); // print a colon
Serial.print(now.minute()); // print the current minute
Serial.print(":"); // print a colon
Serial.println(now.second()); // print the current second and finish the line

Serial.print("The date is: "); // print "The date is: " to the serial monitor
Serial.print(now.day()); // print the current day to the serial monitor
Serial.print("."); // print a full stop / period
Serial.print(now.month()); // print the current month
Serial.print("."); // print a full stop / period
Serial.println(now.year()); // print the current year and finish the line

Serial.print("Today is "); // print "Today is " to the serial monitor
Serial.println(daysOfTheWeek[now.dayOfTheWeek()]); // print the day of the week by using the integer returned by the RTC to look up the word in the daysOfTheWeek array
Serial.println(); // print an empty line

delay(1000); // delay for 1 second

}
