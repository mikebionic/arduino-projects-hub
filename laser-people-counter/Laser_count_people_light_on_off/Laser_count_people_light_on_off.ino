int e1 = A0;
int e2 = A1;
int light = 4;
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

