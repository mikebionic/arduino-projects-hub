#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

int pos = 0;
int oldpos=100;

int sw1=0;
int sw2=0;
int sw3=0;
int sw4=0;
/*int sw1=11;
int sw2=12;
int sw3=13;
int sw4=7;*/


void setup() {
  pinMode (11,INPUT);
  pinMode (12,INPUT); 
  pinMode (13,INPUT);
  pinMode (7,INPUT);
  pinMode (5,OUTPUT);
  
    Serial.begin(9600);
    mySwitch.enableTransmit(10);
}
void loop() {
   sw1=digitalRead (11);
    sw2=digitalRead (12);
     sw3=digitalRead (13);
      sw4=digitalRead (7);
    if (sw1==HIGH){pos=1; Serial.println(pos);}
  //  else {pos=5; Serial.println(pos); }
   else if (sw2==HIGH){pos=2; Serial.println(pos);}
   // else {pos=5; Serial.println(pos); }
   //  mySwitch.send(pos, 23);
   else if (sw3==HIGH){pos=3; Serial.println(pos);}
   // else {pos=5; Serial.println(pos); }
   // mySwitch.send(pos, 23);
   else if (sw4==HIGH){pos=4; Serial.println(pos);}

   else {pos=5; Serial.println(pos); }
    mySwitch.send(pos, 23);
}
