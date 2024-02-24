#include <Stepper.h>
#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
int stepIN1Pin = 2;         
int stepIN2Pin = 3;
int stepIN3Pin = 4;
int stepIN4Pin = 5;
int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, stepIN1Pin, stepIN3Pin, stepIN2Pin, stepIN4Pin);

int joyX=0;
int joyY=1;
int joyVal;
int joyX2=2;
int joyY2=3;
int joyVal2;
int b1=18;
int b2=19;


void setup ()
{
s1.attach(6);
s2.attach(7);
s3.attach(8);
s4.attach(9);
myStepper.setSpeed(15);
pinMode (b1,INPUT);
pinMode (b2,INPUT);
digitalWrite (b1,HIGH);
digitalWrite (b2,HIGH);
}
void loop (){
joyVal = analogRead (joyX);
joyVal = map (joyVal, 0, 1023, 0, 180);
s1.write (joyVal);


joyVal = analogRead (joyY);
joyVal = map (joyVal, 0, 1023, 0, 180);
s2.write (joyVal);
delay(15);

joyVal2 = analogRead (joyX2);
joyVal2 = map (joyVal2, 0, 1023, 0, 180);
s3.write (joyVal2);


joyVal2 = analogRead (joyY2);
joyVal2 = map (joyVal2, 0, 1023, 0, 180);
s4.write (joyVal2);
delay(15);








///////////////////////////////////////////////////////////////////////
int button1State, button2State;
  button1State = digitalRead(b1);
  button2State = digitalRead(b2);
 if (((button1State == LOW) && !(button2State == LOW)))  // if we're pushing button 1 OR button 2
  myStepper.step(stepsPerRevolution/15);
  if (((button2State == LOW) && !(button1State == LOW)))  // if we're pushing button 1 OR button 2
  myStepper.step(-stepsPerRevolution/15);
  //////////////////////////////////////////////////////////////////////////
}



