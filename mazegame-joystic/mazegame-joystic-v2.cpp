#include <Servo.h>
const int ServoXPin = 7;  // X Servo digital pin
const int ServoYPin = 6; // Y Servo digital pin

const int JXpin = A0; //Joystick X pwm pin
const int JYpin = A1; //Joystick Y pwm pin
const int JSpin = 8; //Joystick Select button digital pin

const int Xdiff = -10; // home position for X servo in relation to 90
const int Ydiff = 5; // home position for Y servo in relation to 90

Servo XServo;
Servo YServo;

int Xval;
int Yval;
int JSval;
int Xang; // x servo angle
int Yang; // y servo angle

int Xang_home = 90; // x servo home
int Yang_home = 90; // y servo home

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
  pinMode(ServoXPin, OUTPUT);
  pinMode(ServoYPin, OUTPUT);
  pinMode(JXpin, INPUT);
  pinMode(JYpin, INPUT);
  pinMode(JSpin, INPUT_PULLUP);

  XServo.attach(ServoXPin);
  YServo.attach(ServoYPin);

  Xang = Xang_home; // setting a start place for X angle
  Yang = Yang_home; // setting a start place for Y angle
  XServo.write(Xang);
  YServo.write(Yang);
  delay(1000);
}

void loop() {
  //   put your main code here, to run repeatedly:
  XServo.write(Xang);
  YServo.write(Yang);
  
  Xval = analogRead(JXpin);
  Yval = analogRead(JYpin);
  Serial.print(Xval);
  Serial.println(Yval);

  if (Xval < 500) {
    Xang--;
    XServo.write(Xang);
  }

  if (Xval > 600) {
    Xang++;
    XServo.write(Xang);
  }

  if (Yval < 500) {
    Yang--;
    YServo.write(Yang);
  }

  if (Yval > 600) {
    Yang++;
    YServo.write(Yang);
  }

  JSval = digitalRead(JSpin);


//   if (JSval == 0) {
//     if (Xang < 90 + Xdiff) {
//       for (Xang; Xang < (91 + Xdiff); Xang ++) {
//         XServo.write(Xang);
//         delay(50);
//       }
//     }
//     if (Xang > 90 + Xdiff) {
//       for (Xang; Xang > (89 + Xdiff); Xang --) {
//         XServo.write(Xang);
//         delay(50);
//       }
//     }
//     if (Yang < 90 + Ydiff) {
//       for (Yang; Yang < (91 + Ydiff); Yang ++) {
//         YServo.write(Yang);
//         delay(50);
//       }
//     }
//     if (Yang > 90 + Ydiff) {
//       for (Yang; Yang > (89 + Ydiff); Yang --) {
//         YServo.write(Yang);
//         delay(50);
//       }
//     }
//   }

//   delay(50);
}