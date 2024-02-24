#include "Ultrasonic.h"

Ultrasonic midSonic(12,13);
Ultrasonic rightSonic(10,11);
Ultrasonic leftSonic(4,5);
int rightSonicDist;
int midSonicDist;
int leftSonicDist;
int distThresh = 20;
int distForwardThresh = 40;
int tama_yetdi = 0;
int sag_tarap_bosh = 0;
int cep_tarap_bosh = 0;

// motor
#define cep1 2
#define cep2 7
#define sag1 8
#define sag2 3
#define A 6
#define B 9

int sag_1_state = 0;
int sag_2_state = 0;
int cep_1_state = 0;
int cep_2_state = 0;
// motor

void setup(){
    Serial.begin(9600);

    pinMode (cep1, OUTPUT);
    pinMode (cep2, OUTPUT);
    pinMode (sag1, OUTPUT);
    pinMode (sag2, OUTPUT);
    pinMode (A, OUTPUT);
    pinMode (B, OUTPUT);
    analogWrite(A, 120);
    analogWrite(B, 110);
}

void loop(){
    rightSonicDist = rightSonic.Ranging(CM);
    midSonicDist = midSonic.Ranging(CM);
    leftSonicDist = leftSonic.Ranging(CM);
    

    if (midSonicDist < distThresh){
        tama_yetdi = 1;
        //stop();        
    }

    if (tama_yetdi == 1){
        if (leftSonicDist < distThresh){
            cep_tarap_bosh = 1;        
        } else {
            cep_tarap_bosh = 0;
        }
        if (rightSonicDist < distThresh){
            sag_tarap_bosh = 1;        
        } else {
            sag_tarap_bosh = 0;
        }
    }
    Serial.print("____ Tama yetdimi : _____ ");
    Serial.print(tama_yetdi);
    Serial.print("____ Tama cep_tarap : _____ ");
    Serial.print(cep_tarap_bosh);
    Serial.print("____ Tama sag_tarap : _____ ");
    Serial.println(sag_tarap_bosh);

    if (tama_yetdi == 1 && (cep_tarap_bosh == 1 || sag_tarap_bosh == 1)){
        while (!(midSonicDist < distForwardThresh)){
            midSonicDist = midSonic.Ranging(CM);
            if (cep_tarap_bosh == 1){
                cepe_owrum();
            }
            if (sag_tarap_bosh == 1){
                saga_owrum();
            }
            if (midSonicDist < distForwardThresh){
                tama_yetdi = 0;
                break;
            }
        }
    
    }
    else {
        one_yore();
    }

    log();
    motorRun();
}


void motorRun(){
  digitalWrite(sag1, sag_1_state);
  digitalWrite(sag2, sag_2_state);
  digitalWrite(cep1, cep_1_state);
  digitalWrite(cep2, cep_2_state);
}

void one_yore(){
 sag_1_state = 1;
 sag_2_state = 0;
 cep_1_state = 0;
 cep_2_state = 1;
}

void yza_yore(){
 sag_1_state = 0;
 sag_2_state = 1;
 cep_1_state = 1;
 cep_2_state = 0;
}


void cepe_owrum(){
 sag_1_state = 0;
 sag_2_state = 1;
 cep_1_state = 0;
 cep_2_state = 1;
}


void saga_owrum(){
 sag_1_state = 1;
 sag_2_state = 0;
 cep_1_state = 1;
 cep_2_state = 0;
}


void stop(){
 sag_1_state = 0;
 sag_2_state = 0;
 cep_1_state = 0;
 cep_2_state = 0;
}

void log(){    
    Serial.print(rightSonicDist);
    Serial.print("   ");
    Serial.print(midSonicDist);
    Serial.print("   ");
    Serial.println(leftSonicDist);
}

