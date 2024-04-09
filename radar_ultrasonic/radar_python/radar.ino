#include <Servo.h>


const int trigPin = 10;
const int echoPin = 11;

const float speedOfSound = 0.034656;
long duration;
int distance;
int angle;
Servo servo;

void setup() {
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    servo.attach(12);
    Serial.begin(9600);
    Serial.println("Ready");
}

void loop() {
    if (Serial.available() > 0) {
        angle = Serial.read();
        servo.write(angle);
        delay(10);
        distance = calculateDistance();
        output(angle, distance);
        Serial.flush();
    }
}

void output(int angle, int distance) {
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
}

int calculateDistance() {

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);


    duration = pulseIn(echoPin, HIGH);
    distance = (duration * speedOfSound) / 2;

    return distance;
}