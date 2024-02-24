#include <Servo.h>
Servo s;

const int ldrF=A0;
const int ldrR=A1;
const int ldrL=A2;
int turn=90;
/*int ldrFstatus=0;
int ldrRstatus=0;
int ldrLstatus=0;*/

void setup() {

  Serial.begin(9600);
pinMode (ldrF,INPUT);
  pinMode (ldrL,INPUT);
   pinMode (ldrR,INPUT);

s.attach(12);
//s2.attach(11);
//s.write(turn);
}

void loop() {
   int ldrFstatus=analogRead(ldrF);
 //  delay(5);
   int ldrRstatus=analogRead(ldrR);
 //  delay(5);
   int ldrLstatus=analogRead(ldrL);
 //  delay (5);
  if(ldrLstatus>ldrFstatus){turn=turn+1; /*s.write(turn);*/}
  if(ldrRstatus>ldrFstatus){turn=turn-1; /*s.write(turn);*/}
  turn=constrain(turn,0,180);
  s.write(turn);
  Serial.println(ldrLstatus);
  Serial.println(ldrRstatus);
  Serial.println(ldrFstatus);
}
