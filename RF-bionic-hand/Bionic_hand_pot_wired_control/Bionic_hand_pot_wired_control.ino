#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
int const p1 = A1;
int const p2 = A2;
int const p3 = A3;
int const p4 = A4;
int const p5 = A5;
int val1; 
int val2; 
int val3; 
int val4; 
int val5; 
int angle1;
int angle2;
int angle3;
int angle4;
int angle5;

void setup() {
  Serial.begin(9600);
 s1.attach(2);
 s2.attach(3);
 s3.attach(4);
 s4.attach(5);
 s5.attach(6);
}

void loop() {
  val1 = analogRead(p1); 
    val2 = analogRead(p2);
      val3 = analogRead(p3);
        val4 = analogRead(p4);  
          val5 = analogRead(p5);
  angle1 = map(val1, 0, 1023, 0, 179);
  angle2 = map(val2, 0, 1023, 0, 179);
  angle3 = map(val3, 0, 1023, 0, 179);
  angle4 = map(val4, 0, 1023, 0, 179);
  //angle5 = map(val5, 0, 1023, 0, 179);
Serial.print (val1);
Serial.print (" ");
Serial.print (angle1);
Serial.print (" ");
Serial.println (angle2);
/*Serial.print (" ");
Serial.print (angle1);
Serial.print (" ");
Serial.print (angle1);
Serial.print (" ");*/
  
  s1.write(angle1);
  
  s2.write(angle2);
 
 s3.write(angle3);
  //delay (15);
 s4.write(angle4);
  //delay (15);
 s5.write(angle5);
 // delay (15);*/
}
