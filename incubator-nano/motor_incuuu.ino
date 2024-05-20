int s1 =2;
int s2 =3;
int led1=10;
int led2=5;
int sw1;
int sw2;
int a=0; 
int b=0;
long y=millis();
unsigned long timer;


void setup() {
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
  if (millis() - timer >= 100){
    timer = millis();
  }
  sw1=digitalRead (s1);
  sw2=digitalRead(s2);

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
    while (y+10000<millis()){
    digitalWrite (led1,1);
    Serial.println("sig1");
      timer=millis();
      y=millis();
    }
  }
  if (a==0 && b==1){ 
    digitalWrite (led1,0);
    while (y+10000<millis()){
      digitalWrite (led2,1);
      Serial.println("sig2");
      timer=millis();
      y=millis();
    }
  }
}

