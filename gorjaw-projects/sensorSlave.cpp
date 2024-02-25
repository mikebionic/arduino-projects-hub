#include <dht.h>
int dhtSensor = 5;
dht = DHT;
long x=millis();
// gas sensor
int gasSensor = A0;
int gasThreshold = 400;
int waterSensor = 15; // 15 or A1
// indicators and states
int buzzer = 11;
int greenIndicator = 12;
int redIndicator = 13;
// relays and throttles
int wentilationFan = 6;
int heaterRelay = 7;
int windowRelay = 8;
int gasThrottle = 9;
int waterThrottle = 10;

// treshold of temperature
int minTempTresh = 10;
int maxTempTresh = 25;

String stream;
SoftwareSerial master (2,3);

void setup() {
  pinMode(gasSensor,INPUT);
  pinMode(waterSensor,INPUT_PULLUP);

  pinMode(greenIndicator, OUTPUT);
  pinMode(redIndicator, OUTPUT);
  pinMode(windowRelay, OUTPUT);
  pinMode(heaterRelay, OUTPUT);
  pinMode(gasThrottle, OUTPUT);
  pinMode(waterThrottle, OUTPUT);
  pinMode(wentilationFan, OUTPUT);
  // stabilize the relays and outputs
  digitalWrite(gasThrottle,0);
  digitalWrite(waterThrottle,0);
  digitalWrite(wentilationFan,0);
  digitalWrite(heaterRelay,0);
  digitalWrite(windowRelay,0);

  Serial.begin(9600);
  master.begin(9600);
}

void loop() {
  if (master.available()){
    stream = master.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      if (stream == "1ach"){
        Serial.println("planZat")
      }
    }
  }
  gas();
  temp();
  heater();
  water(); 
}

void gas(){
  int analogSensor = analogRead(gasSensor);
  if (analogSensor>gasThreshold){
    digitalWrite(greenIndicator,0);
    digitalWrite(redIndicator,1);
    digitalWrite(gasThrottle,1);
    digitalWrite(wentilationFan,1);
    tone(buzzer,1000,200);
  }
  else{
    digitalWrite(greenIndicator,1);
    digitalWrite(redIndicator,0);
    digitalWrite(gasThrottle,0);
    digitalWrite(wentilationFan,0);
    noTone(buzzer);
  }
}

void temp(){
  if((x+4000)<millis()){
    float readData = DHT.read11(dhtSensor);
    unsigned int t=DHT.temperature;
    unsigned int h=DHT.humidity;
    Serial.println(t);
    x=millis();
  }
}

void heater(){
  if(DHT.temperature<minTempTresh){
    // digitalWrite(windowRelay,1);
    digitalWrite(heaterRelay,1);
  }
  else if(DHT.temperature>maxTempTresh){
    digitalWrite(heaterRelay,0);
    // digitalWrite(windowRelay,0)
  }
}

void water(){
  int waterState = digitalRead(waterSensor)
  if(waterState==0){
    // digitalWrite(windowRelay,1);
    digitalWrite(waterThrottle,1);
    tone(buzzer,700,200);
  }
  else{
    digitalWrite(waterThrottle,0);
    // digitalWrite(windowRelay,0)
  }
}