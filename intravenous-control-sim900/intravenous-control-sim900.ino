#include <GSM.h>
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
//int button = 4;
const int ldrPin = A0;
const int p = 3;

/**************************************************************/
char num[20] = {'+','9','9','3','6','2','7','5','2','0','8','4'}  //Write here number who recieve sms. Write number like example variable "num"
/**************************************************************/

;String txtMsg = "5% Galdy!!!";
boolean light=false;
boolean last=false;

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  //pinMode(p, OUTPUT);
  Serial.println("Kapelnisa");
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Catylmadyk");
      delay(1000);
    }
  }
//  pinMode(button,INPUT);
  Serial.println("GSM ise tayyar");
}


void loop() {
  int ldrStatus = analogRead(ldrPin);
  last=light;
  //if (ldrStatus >=905){tone (p,500);} else {tone (p,0);}
  if(ldrStatus >=905){light=true;} else {light=false; }
  Serial.print("last="); Serial.println(last);
   Serial.print("light="); Serial.println(light);
   Serial.print(ldrStatus);
  if (light==true && last==false) {
  sms.beginSMS(num);
  sms.print(txtMsg);
  sms.endSMS();
  Serial.println("\nIberdi\n");
  //delay (8000);tone (p,0);
  
   }
}

