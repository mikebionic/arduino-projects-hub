#include "Ultrasonic.h"

Ultrasonic midSonic(10,11);
Ultrasonic leftSonic(12,13);
Ultrasonic rightSonic(8,9);
int rightSonicDist;
int midSonicDist;
int leftSonicDist;
int distThresh = 13;
int frontDistThresh = 20;
int smallestDistThresh = 8;


#define sag1 3
#define sag2 2
#define cep1 7
#define cep2 4
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
    analogWrite(enA, 100);    
    analogWrite(enB, 100);
}

void loop(){
    updateDistanceValues();
    calculate_and_run();

    digitalWrite(sag1,sag1_state);
    digitalWrite(sag2,sag2_state);
    digitalWrite(cep1,cep1_state);
    digitalWrite(cep2,cep2_state);   

}

void updateDistanceValues(){
    rightSonicDist = rightSonic.Ranging(CM);
    midSonicDist = midSonic.Ranging(CM);
    leftSonicDist = leftSonic.Ranging(CM);
    Serial.print(leftSonicDist);
    Serial.print("     ");
    Serial.print(midSonicDist);
    Serial.print("     ");
    Serial.println(rightSonicDist);
}
void calculate_and_run(){
    while (rightSonicDist < frontDistThresh && midSonicDist < frontDistThresh){
			// hard turning
			Serial.println("+++++++++++++++++++++++   hard turning left");
			left();
			
			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);   
			midSonicDist = midSonic.Ranging(CM);

			//updateDistanceValues();
			if (midSonicDist > frontDistThresh + 10){
					Serial.println("______________ breaking ______________");
					break;
			}
			//delay(3000);
    }
    while (leftSonicDist < frontDistThresh && midSonicDist < frontDistThresh){
			// hard turning
			Serial.println("+++++++++++++++++++++++   hard turning right");
			right();
			
			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);   
			midSonicDist = midSonic.Ranging(CM);
			//updateDistanceValues();
			if (midSonicDist > frontDistThresh + 10){
					Serial.println("______________ breaking ______________");
					break;
			}
			
			//delay(3000);
    }
    if (rightSonicDist < distThresh && midSonicDist > frontDistThresh){
			// soft turning
			Serial.println("+++++++++++++++++++++++   soft turning right_slow");
			left_slow();
			
			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);   
    }
    if (leftSonicDist < distThresh && midSonicDist > frontDistThresh){
			// soft turning
			Serial.println("+++++++++++++++++++++++   soft turning left_slow");
			right_slow();
			
			digitalWrite(sag1,sag1_state);
			digitalWrite(sag2,sag2_state);
			digitalWrite(cep1,cep1_state);
			digitalWrite(cep2,cep2_state);   
    }


    if (leftSonicDist > frontDistThresh && midSonicDist < smallestDistThresh && rightSonicDist > frontDistThresh){
        if (rightSonicDist < leftSonicDist){
            left();
        }
        if (leftSonicDist < rightSonicDist){
            right();
        }
        digitalWrite(sag1,sag1_state);
        digitalWrite(sag2,sag2_state);
        digitalWrite(cep1,cep1_state);
        digitalWrite(cep2,cep2_state);   
    }

    if (leftSonicDist > frontDistThresh && midSonicDist > frontDistThresh && rightSonicDist > frontDistThresh) {
        forward();
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