#include <Servo.h>// include Servo library
// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 180; // 90; // stand horizontal servo
int servohLimitHigh = 180;
int servohLimitLow = 0;
// 65 degrees MAX
Servo vertical; // vertical servo
int servov = 45; // 90; // stand vertical servo
int servovLimitHigh = 179;
int servovLimitLow = 20;
// LDR pin connections
// name = analogpin;
int ldrlt = 0; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT
int ldrld = 2; //LDR down left - TOP LEFT
int ldrrd = 3; //ldr down rigt - TOP RIGHT

int joyX=4;
int joyY=5;
int joyVal;
int joyVal2;
int rotate;
int top;
int b1=2;
//????????????????????????
boolean lastB=LOW;
boolean curB=LOW;
boolean s3On=false;
//????????????????????????


void setup()
{ Serial.begin(9600);
// servo connections
// name.attacht(pin);
horizontal.attach(9);
vertical.attach(8);
horizontal.write(180);
vertical.write(45);
delay(3000);
rotate=88;
top=88;
pinMode (b1,INPUT);
digitalWrite(b1,HIGH);
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

  
void loop()
{ 
  /////////////////////////////////////////////
  curB=debounce(lastB);
  
 if (lastB==LOW && curB ==HIGH) 
 
 {s3On=!s3On;

 }

  lastB= curB;
  
 if (s3On==LOW){
 
  joyVal = analogRead (joyY);
joyVal = map (joyVal, 0, 1023, 0, 180);
if (joyVal>120) {top=top+4;}
if (joyVal<50) {top=top-4;}
top=constrain(top,30,160);
vertical.write (top);
//delay (10);
joyVal2 = analogRead (joyX);
joyVal2 = map (joyVal2, 0, 1023, 0, 180);
if (joyVal2<120) {rotate=rotate+4;}
if (joyVal2> 50) {rotate=rotate-4;}
rotate=constrain(rotate,0,180);
horizontal.write (rotate);
delay(10);
 }
////////////////////////////////////////////


else{
  
int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left

int rd = analogRead(ldrrd); // down right
// int dtime = analogRead(4)/20; // read potentiometers
// int tol = analogRead(5)/4;
int dtime = 10; int tol = 50;
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt
Serial.print(avt);
Serial.print(" ");
Serial.print(avd);
Serial.print(" ");
Serial.print(avl);
Serial.print(" ");
Serial.print(avr);
Serial.print(" ");
Serial.print(dtime);
Serial.print(" ");
Serial.print(tol);
Serial.println(" ");
if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
{
if (avt > avd)
{
servov = ++servov;
if (servov > servovLimitHigh)
{
servov = servovLimitHigh;
}
}
else if (avt < avd)
{
servov= --servov;
if (servov < servovLimitLow)
{
servov = servovLimitLow;
}
}
vertical.write(servov);
}
if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
{
if (avl > avr)
{
servoh = --servoh;
if (servoh < servohLimitLow)
{
servoh = servohLimitLow;
}
}
else if (avl < avr)
{
servoh = ++servoh;
if (servoh > servohLimitHigh)
{
servoh = servohLimitHigh;
}
}
else if (avl = avr)
{
// nothing
}
horizontal.write(servoh);
}
delay(dtime);
}}
