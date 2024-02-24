#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte per[8] = 
{
  0b00100,
  0b00000,
  0b01110,
  0b10101,
  0b00100,
  0b01010,
  0b10001,
  0b00000
};


int e1 = A0;
int e2 = A1;
int light = 7;
int person = 0;
long x;
long ptime = 0;
#define  first analogRead(e1)
#define  second analogRead(e2)
#define  light_on digitalWrite(light,1)
#define  light_off digitalWrite(light,0)
void setup(){
Serial.begin(9600);
ptime = millis();
pinMode(light,OUTPUT);
 lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Binanyn icindaki");
    lcd.setCursor(2,1);
    lcd.print("adam");
  lcd.createChar(1, per);
  
 // lcd.setBacklight(0x1);
}

void loop(){
if(first < 950){
x = millis();
  while((x + 800) > millis()){
    if(second < 900){increase();delay(500);break;}
  }
}
else if(second < 950){
x = millis();
  while((x + 800) > millis()){
    if(first < 900){decrease();delay(500);break;}
  }
}
if(person > 0){light_on;}
else {light_off;}

if((ptime + 100) < millis()){
 ptime = millis();
 Serial.println("1 : " + (String)first + " 2 : " + (String)second + " Person : " + (String) person);
 //Serial.println(person);
 ///////////////////////////////////////
 lcd.setCursor(8,1);
    lcd.print(person);
    lcd.print(" ");
    lcd.write(1);
    /////////////////////////////////////
}

}
void increase(){
  person++;
  
}
void decrease(){
person--;
if(person < 0){
  person = 0;
}
}

