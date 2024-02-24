int s1 =14;
int s2 =15;
int led1=16;
int led2=17;
int sw1=0;
int sw2=0;
int a=0; 
int b=0;
long y=millis();
#include "SevSeg.h"

//Create an instance of the object.
SevSeg myDisplay;

//Create global variables
unsigned long timer;
int deciSecond = 0;

void setup() {
  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode
int digit1 = 10; 
  int digit2 = 11; 
  int digit3 = 12; 
  int digit4 = 13; 
 
  int segA = 2;  
  int segB = 3; 
  int segC = 4; 
  int segD = 5; 
  int segE = 6; 
  int segF = 7; 
  int segG = 8; 
  int segDP= 9;
  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display
  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  myDisplay.SetBrightness(100); //Set the display to 100% brightness level
  timer = 0;
  
  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode (led1,OUTPUT);
pinMode (led2,OUTPUT);
pinMode (s1,INPUT_PULLUP);
pinMode (s2,INPUT_PULLUP);
digitalWrite (led1,1);
}

void loop() {
   char tempString[10]; //Used for sprintf
  sprintf(tempString, "%4d", deciSecond);
    myDisplay.DisplayString(tempString, 3);
if (millis() - timer >= 100)
  {
    timer = millis();
    deciSecond++;
  }

  delay(5);
    
  // put your main code here, to run repeatedly:
 sw1=digitalRead (s1);
sw2=digitalRead(s2);

/////////////////////////////////////////////
  if (sw1==LOW && sw2==HIGH){
  a=1;
  b=0;
}
if (sw2==LOW && sw1==HIGH){
  a=0;
  b=1;
}
if (a==1 && b==0){ 
   digitalWrite (led2,0);
  while (y+1440000<millis()){
  
  digitalWrite (led1,1);
  Serial.println("sig1");
 // int deci=1;
    deciSecond = 0;
    timer=millis();
    y=millis();
    //deci=0;
  //  return deci;
  }
}
if (a==0 && b==1){ 
  digitalWrite (led1,0);
    while (y+1440000<millis()){
   
  digitalWrite (led2,1);
  Serial.println("sig2");
    deciSecond = 0;
    timer=millis();
    y=millis();
    }
}
}
