
int led = 13;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int bn=0;
int bn5=0;
int bn2=0;
int bn3=0;
int bn4=0;
int a=0;
int l;
int r;
int LedList[]={led1,led2,led3,led4,led5};
 long x;
 
 // boolean light=false;
 // boolean light_off=false;
void setup() {
  Serial.begin (9600);
  pinMode(8,INPUT_PULLUP);
   pinMode(9,INPUT_PULLUP);
    pinMode(10,INPUT_PULLUP);
     pinMode(11,INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
}

void loop() {
 bn = digitalRead(8);
 bn2 = digitalRead(9);
 bn3= digitalRead(10);
 bn4 = digitalRead(11);
 bn5 = digitalRead(12);
 

  if(bn ==LOW){
    digitalWrite(LedList[l],0);
    x = millis();
    digitalWrite(led,LOW);
    noTone(7);
  }

  if (bn2==LOW){
    a=5000;
  }
    if (bn3==LOW){
    a=8000;
  }
    if (bn4==LOW){
    a=10000;
  }
  //  if (bn5==LOW){
//    a=13000;
//  }
        if((x + a)<millis()){
            digitalWrite(led,HIGH);
            tone (7,1000);
            delay (100);
            noTone(7);
            delay (100);
            tone (7,700);
    }
    
 // digitalWrite(LedList[4],HIGH);
 
 // digitalWrite (LedList[4],1);
   //l =    map (millis(),x,x+a,LedList[0],LedList[4]);
        digitalWrite (LedList[l],1);
//  }
    Serial.print(millis());
      Serial.print("   ");
  Serial.print(x);
    Serial.print("   ");
  Serial.println(a);
  }
  
