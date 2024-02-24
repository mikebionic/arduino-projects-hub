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
int joyVal3;
int joyVal4;
int hand;
int rotate;
int body;
//????????????????????????
boolean lastB=LOW;
boolean curB=LOW;
boolean s3On=false;
//????????????????????????

void setup ()
{Serial.begin(9600);
s1.attach(6);
s2.attach(7);
s3.attach(8);
s4.attach(9);
myStepper.setSpeed(15);
pinMode (b1,INPUT);
pinMode (b2,INPUT);
digitalWrite (b1,HIGH);
digitalWrite (b2,HIGH);
hand=88;
rotate=88;
body=88;
}

////////////////////////////////////
boolean debounce(boolean last)
{
  boolean cur=digitalRead (b1);
  if (last!=cur);
  {
    delay(5);
    cur=digitalRead (b1);
  }
  return cur;}
  //////////////////////////////////



  
void loop (){

  
/////////////////////////////////////
curB=debounce(lastB);
  
 if (lastB==LOW && curB ==HIGH) 
 
 {s3On=!s3On;

 }

  lastB= curB;
 if (s3On==HIGH){
 s3.write(180);}else{s3.write(0);};
 ////////////////////////////////////////////


  
joyVal = analogRead (joyX);
joyVal = map (joyVal, 0, 1023, 0, 180);
if (joyVal>120) {body=body+5;}
if (joyVal<50) {body=body-5;}
body=constrain(body,0,180);
//rotate = map (rotate, 88, 180, 88, 180);
s2.write (body);



joyVal2 = analogRead (joyY);
joyVal2 = map (joyVal2, 0, 1023, 0, 180);
delay(10);

joyVal3 = analogRead (joyX2);
joyVal3 = map (joyVal3, 0, 1023, 0, 180);
if (joyVal3>120){hand=hand+5;}
if (joyVal3<50){hand=hand-5;}
hand=constrain(hand,0,180);
/*if (joyVal3>179){hand=hand+20;}
if (joyVal3<10){hand=hand-20;}*/
s1.write (hand);


joyVal4 = analogRead (joyY2);
joyVal4 = map (joyVal4, 0, 1023, 0, 180);
if (joyVal4>120) {rotate=rotate+5;}
if (joyVal4<50) {rotate=rotate-5;}
rotate=constrain(rotate,0,180);
//rotate = map (rotate, 88, 180, 88, 180);
s4.write (rotate);
delay(10);



  ///////////////////////////////////////////////////////////////////////

 if (joyVal2>150)  // if we're pushing button 1 OR button 2
  myStepper.step(stepsPerRevolution/15);
  if (joyVal2<30)  // if we're pushing button 1 OR button 2
  myStepper.step(-stepsPerRevolution/15);
  //////////////////////////////////////////////////////////////////////////

 }



