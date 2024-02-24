 
#include <HT1621.h> // include our library


HT1621 lcd; // create an "lcd" object

int trigPin=6; //Sensor Trip pin connected to Arduino pin 13
int echoPin=7;  //Sensor Echo pin connected to Arduino pin 11
int myCounter=0;  //declare your variable myCounter and set to 0
int servoControlPin=6; //Servo control line is connected to pin 6
float pingTime;  //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches 
float speedOfSound=776.5; //Speed of sound in miles per hour when temp is 77 degrees.

 void setup() {
  
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);


  lcd.begin(13, 12, 8, 10); // (cs, wr, Data, backlight)
  // if no backlight control is given, you can also use:
  // lcd.begin(13, 12, 8); // (cs, wr, Data)

  lcd.backlight(); // turn on the backlight led

  lcd.clear(); // clear the screen
}


void loop() {
  
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state
  
  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //переводишь в секунды convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //переводишь в часы convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;  // переводишь в мили получаешь расстояние This will be in miles, since speed of sound was miles per hour
  targetDistance=targetDistance/2; // Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= 225-targetDistance*160934,4;    // переводишь в сантиметры Convert miles to cm by multipling by 63360 (inches per mile)
  
  lcd.print(targetDistance); //Print measured distance
  delay(1000); //pause to let things settle
   
  
  
  }  

