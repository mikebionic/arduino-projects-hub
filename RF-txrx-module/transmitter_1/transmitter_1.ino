#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int hozdead= 507 ;
int verdead= 503 ;
int pos = 0;
int oldpos=100;
int val = 0;
int val2 = 0;
void setup() {
    Serial.begin(9600);
    mySwitch.enableTransmit(10);
}
void loop() {
    //Read JoyStick
   val = analogRead(0);
    val2 = analogRead(1);
    Serial.println(val);
    Serial.println(val2);
    //UP 1
    if (val> verdead+10){pos=1; Serial.println(pos);}
    //DOWN 2
    if (val< verdead-10){pos=2; Serial.println(pos);}
    //RIGHT 3
    if (val2> hozdead+10){pos=4; Serial.println(pos);}
    //LEFT 4
    if (val2< hozdead-10){pos=3; Serial.println(pos);}
    //DEAD ZONE 5
    if (val>verdead-20 && val< verdead+20 && val2>hozdead-20 && val2< hozdead+20)
    {
         pos=5; Serial.println(pos);
    }
    mySwitch.send(pos, 23);
}
