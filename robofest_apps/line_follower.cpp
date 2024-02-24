#include "Ultrasonic.h"

int midSensor = A2;
int leftSensor = A0;
int rightSensor = A1;
int rightSensor_state;
int midSensor_state;
int leftSensor_state;
int distThresh = 13;
int frontDistThresh = 20;
int smallestDistThresh = 8;
int lastTurn = 1;


#define sag1 3
#define sag2 2
#define cep1 4
#define cep2 7
#define enA 6
#define enB 5

int sag1_state = 0;
int sag2_state = 0;
int cep1_state = 0;
int cep2_state = 0;

void setup() {
    Serial.begin(9600);
    pinMode(sag1, OUTPUT);
    pinMode(sag2, OUTPUT);
    pinMode(cep1, OUTPUT);
    pinMode(cep2, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);


    pinMode(midSensor, INPUT);
    pinMode(leftSensor, INPUT);
    pinMode(rightSensor, INPUT);

    analogWrite(enA, 100);
    analogWrite(enB, 100);
}

void loop(){
	updateColorValues();
	calculate_and_run();

	digitalWrite(sag1,sag1_state);
	digitalWrite(sag2,sag2_state);
	digitalWrite(cep1,cep1_state);
	digitalWrite(cep2,cep2_state);
}

void updateColorValues(){
    rightSensor_state = digitalRead(rightSensor);
    midSensor_state = digitalRead(midSensor);
    leftSensor_state = digitalRead(leftSensor);
    Serial.print(leftSensor_state);
    Serial.print("     ");
    Serial.print(midSensor_state);
    Serial.print("     ");
    Serial.println(rightSensor_state);
}
void calculate_and_run(){

    if (rightSensor_state == 1 && leftSensor_state == 0){
			// hard turning
			Serial.println("+++++++++++++++++++++++   hard turning left");
			
            lastTurn = 2;
            right_slow();

            analogWrite(enA, 100);
            analogWrite(enB, 100);

			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);

    }
    if (leftSensor_state == 1 && rightSensor_state == 0){
			// hard turning
			Serial.println("+++++++++++++++++++++++   hard turning right");
			lastTurn = 0;
            left_slow();

            analogWrite(enA, 100);
            analogWrite(enB, 100);

			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);
			
    }
    if(rightSensor_state == 1 && leftSensor_state == 0 && midSensor_state == 1){
			// soft turning
			Serial.println("+++++++++++++++++++++++   soft turning right_slow");
			right_slow();

			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);
    }
    if(leftSensor_state == 1 && rightSensor_state == 0 && midSensor_state == 1){
			// soft turning
			Serial.println("+++++++++++++++++++++++   soft turning left_slow");
            left_slow();

			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);
    }


    if(leftSensor_state == 0 && rightSensor_state == 0 && midSensor_state == 1) {

        forward();
    }
    if (leftSensor_state == 0 && rightSensor_state == 0 && midSensor_state == 0){

        if (lastTurn == 2){
            right_slow();

            analogWrite(enA, 120);
            analogWrite(enB, 120);
        }

        if (lastTurn == 0){
            left_slow();

            analogWrite(enA, 120);
            analogWrite(enB, 120);
        }
    }
}

void forward(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 1;
    cep2_state = 0;
}

void right(){
    sag1_state = 1;
    sag2_state = 0;
    cep1_state = 1;
    cep2_state = 0;
}

void left(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 0;
    cep2_state = 1;
}
void right_slow(){
    sag1_state = 0;
    sag2_state = 0;
    cep1_state = 1;
    cep2_state = 0;
}

void left_slow(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 0;
    cep2_state = 0;
}