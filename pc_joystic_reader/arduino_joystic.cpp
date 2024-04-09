#include <Servo.h>
Servo x_servo;
Servo y_servo;

int xaxis_pot = A0;
int yaxis_pot = A1;
int xaxis_value;
int yaxis_value;
int joybutton = 8;
int joybutton_state;

int xjoygyro_state = 50;
int yjoygyro_state = 50;

void setup() {
    pinMode(joybutton, INPUT);
    x_servo.attach(6);
    y_servo.attach(7);
    Serial.begin(9600);
}

void loop() {
    axis_reader();
//    joygyro_mapper();
//    servo_controller();    
    logger();
}

void axis_reader(){
    xaxis_value = analogRead(xaxis_pot);
    yaxis_value = analogRead(yaxis_pot);
    joybutton_state = digitalRead(joybutton);
}

void joygyro_mapper(){
    xjoygyro_state = map(xaxis_value, 1, 1023, 1, 500);
    yjoygyro_state = map(yaxis_value, 1, 1023, 1, 500);
}

void servo_controller() {
    x_servo.write(map(xaxis_value, 1, 1023, 1, 170));
    y_servo.write(map(yaxis_value, 1, 1023, 1, 170));
    delay(15);
}

void logger(){
     Serial.print(xaxis_value);
     Serial.print(" : ");
     Serial.print(yaxis_value);
     Serial.print(" : ");
     Serial.println(joybutton_state);
    // Serial.print(" ");
    // Serial.print(joybutton_state);
    // Serial.print(" ---- ");
    // Serial.print(xjoygyro_state);
    // Serial.print(" ");
    // Serial.println(yjoygyro_state);
}