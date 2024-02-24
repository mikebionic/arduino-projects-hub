#include <Servo.h>
#include <dht.h>
#define dhtData 6
#define heaterRelay 5
#define pumpRelay 4
#define windowServo 3
Servo s;
dht DHT;

long x=millis();
long y=millis();

// period of time to water plants (in millis)
// 12 hours = 43200000 millis
int wateringPeriodMillis = 43200000;
// Treshhold of humidiry
int treshHumidity = 40;

// Treshhold of temperature
int maxTempTresh = 20;
int minTempTresh = 10;

// Servo states degrees
// replace with your values
int closedServoState = 20;
int openedServoState = 100;

void setup() {
  Serial.begin(9600);
  pinMode(heaterRelay,OUTPUT);
  pinMode(pumpRelay,OUTPUT);
  digitalWrite(pumpRelay,0);
  digitalWrite(heaterRelay,0);
  s.attach(windowServo);
  s.write(closedServoState);
}

void loop() {
  temp();
  heater();
  servo();
  pumpWatering();
}

void heater(){
  if(DHT.temperature<=minTempTresh ) {
    digitalWrite (heaterRelay,1);
    s.write(closedServoState);
  }
  else if(DHT.temperature>maxTempTresh) {
    digitalWrite (heaterRelay,0);
    s.write(openedServoState);
  } 
}

void temp(){
  if ((x+4000)<millis()){ 
    float readData = DHT.read11(dhtData);
    unsigned int t=DHT.temperature;
    unsigned int h=DHT.humidity;
    Serial.print ("Temp = ");
    Serial.print (t);
    Serial.print (" *C ");
    Serial.print ("Cyglylyk ");
    Serial.print (h);
    Serial.println (" %");
    x=millis();
  }
}

void pumpWatering(){
  if ((y+wateringPeriodMillis)<millis()){
    digitalWrite(pumpRelay,1);
    delay(7000);
    digitalWrite(pumpRelay,0);
    y=millis();
  }
}

void servo(){
  if (DHT.humidity>treshHumidity){
    s.write(openedServoState);
  }
  else{
    s.write(closedServoState);
    }
}