#include <Servo.h>
Servo myservo;
Servo gunservo;
const int trigPin = 10;
const int echoPin = 11;

const float speedOfSound = 0.034656;
long duration;
int distance;

int servoRotation = 1;
int rotationStep = 1;
int gun_reloaded = 1;
int reload_btn = 7;


void print(int rot, int dist) {
  Serial.print(rot);
  Serial.print(",");
  Serial.println(dist);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  pinMode(reload_btn, INPUT_PULLUP);

  Serial.begin(9600);
  myservo.attach(12);
  gunservo.attach(13);
  myservo.write(servoRotation);
  gunservo.write(10);
}

void loop() {
  distance = calculateDistance();

  int reload_btn_state = digitalRead(reload_btn);
  if (reload_btn_state == 0){
    gun_reloaded = 1;
  }

  if (gun_reloaded == 1){
    print(servoRotation, distance);

    if (distance < 40 && distance != 0){
       shoot();
    }

    myservo.write(servoRotation);
    if(servoRotation >= 180) {
      rotationStep *= -1;
    } else if(servoRotation <= 0) {
      rotationStep *= -1;
    }
    servoRotation += rotationStep;
    delay(15);
  }
  
}

int calculateDistance() {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration * speedOfSound) / 2;
    return distance;
}

void shoot(){
  if (gun_reloaded == 1){
    gunservo.write(100);
    tone(6,100);
    delay(300);
    gunservo.write(10);
    gun_reloaded = 0;
    delay(3000);
    noTone(6);
  }
}

//
//void sound() {
//  if (sound_millis < millis()+5000){
//    tone(6,100);
//  } else {
//    noTone(6);
//  }  
//}


