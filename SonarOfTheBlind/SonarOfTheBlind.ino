#include <Ultrasonic.h>
Ultrasonic ultrasonic(A0,A1);
 int Height;
 #define pwm 3
int val;
void setup() {
  Serial.begin(9600);
  
pinMode (pwm,OUTPUT);
//digitalWrite (3,HIGH);
     }

void loop()
{
  Height=(ultrasonic.Ranging(CM));
 Serial.println(Height);
      //delay(1000);00
      val = map (Height, 200,10, 0,200);
     analogWrite (pwm,val);
     if (Height>150){
      digitalWrite(pwm,LOW);
     }
  }




