#include <Servo.h>
#include "Ultrasonic.h"

Servo clawServo;
Servo frontServo;
Servo backServo;
Servo baseServo;

Ultrasonic outSonic(12,13);
int outSonicDist;
Ultrasonic inSonic(10,11);
char stream = 0;
int inSonicDist;
int inSonicThresh = 4;
int outSonicThresh = 10;
int box_is_out = 0;
int continue_after_value_save = 0;
int prepare_after_box_done = 0;
int box_released_mode = 0;

int inIrSensor = A0;
int outIrSensor = A1;
int inIrSensor_value;
int outIrSensor_value;
int inIrSensor_value_saved;
int outIrSensor_value_saved;

int boxChannel_closedVal = 60;
int boxChannel_openedVal = 10;
int boxGate_closedVal = 180;
int boxGate_openedVal = 60;
int out_box_detected = 0;
long out_box_millis;

Servo boxChannel;
Servo boxGate;

int conveyMotor = 8;
int conveyMotorState = 0;


int boxDetected = 0;



int korobka_suysh_millis;
int korobka_suysh_action = 0;

void setup(){
    Serial.begin(9600);
    clawServo.attach(2);
    frontServo.attach(3);
    backServo.attach(4);
    baseServo.attach(5);
    boxChannel.attach(6);
    boxGate.attach(7);

    pinMode(conveyMotor, OUTPUT);
    prepare_box_servo();
    //cep_owrum();
    //yokary_gal();
    //korobka_gys();
    starting_state();
}


void readIrSensors(){
    inIrSensor_value = digitalRead(inIrSensor);
    outIrSensor_value = digitalRead(outIrSensor);
}

void inSonicHandler(){
	if (boxDetected == 0){
		if (inSonicDist < inSonicThresh){
            inIrSensor_value_saved = inIrSensor_value;
            boxDetected = 1;
		}
	}
}


void readUltrasonics(){
    outSonicDist = outSonic.Ranging(CM);
    inSonicDist = inSonic.Ranging(CM);

    //Serial.print("ConveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeYYY ___ ");
    //Serial.println(conveyMotorState);
    //Serial.print("ultrasonicsss ___ ");
    //Serial.print(inSonicDist);
    //Serial.print("    ___    ");
    //Serial.println(outSonicDist);
}


void loop(){
    //if inIrSensor_value == 1 -> Black box
    //if inIrSensor_value == 0 -> white box
    korobka_suysh();
    if (Serial.available()>0){
        stream = Serial.read();
        if (stream == '1'){
            korobka_suysh_call();
        }
        if (stream == '2'){
            korobka_gys();
        }
        if (stream == '3'){
            korobka_goyber();
        }
        if (stream == '4'){
            yokary_gal();
        }
        if (stream == '5'){
            sag_owrum();
        }
        if (stream == '6'){
            cep_owrum();
        }
        if (stream == '7'){
            one_goymaga_suysh();
        }
        if (stream == '8'){
            korobka_owrul();
        }
        
    }
    readUltrasonics();
    readIrSensors();

    if (boxDetected == 1){
        if (outSonicDist < outSonicThresh){
            out_box_detected = 1;
            out_box_millis = millis();
            stop_conveyer();
        }
    }
    if (out_box_detected){
        stop_conveyer();
        Serial.println(out_box_millis);
        if (outSonicDist < outSonicThresh){
            out_box_millis = millis();
        }

        if (out_box_millis + 2000 < millis()){
            if (!(outSonicDist < outSonicThresh)){
                out_box_detected = 0;
                boxDetected = 0;
            }
        }
    }		

    if (boxDetected == 0){
        if (!(inSonicDist < inSonicThresh)){
            stop_conveyer();
            closeGate();
            openChannel();
        }
        inSonicHandler();
    }
    else if (boxDetected == 1 && !out_box_detected){
        openGate();
        closeChannel();
        start_conveyer();
    }

    digitalWrite(conveyMotor, conveyMotorState);
}

void prepare_box_servo(){
    boxChannel.write(boxChannel_openedVal);
    boxGate.write(boxGate_closedVal);
}

void closeGate(){
	boxGate.write(boxGate_closedVal);
}
void openGate(){
	boxGate.write(boxGate_openedVal);
}
void closeChannel(){
	boxChannel.write(boxChannel_closedVal);
}
void openChannel(){
	boxChannel.write(boxChannel_openedVal);
}

void release_box_servo(){
    boxChannel.write(boxChannel_closedVal);
    boxGate.write(boxGate_openedVal);
}

void box_in_ready_handler(){
    if (inSonicDist < inSonicThresh){
        boxChannel.write(boxChannel_closedVal);
    }
    else {
        if (box_released_mode == 1){
            start_conveyer();
        }
    }
}

void korobka_suysh_call(){
    long korobka_suysh_millis = millis();
    korobka_suysh_action = 1;
}

void korobka_suysh(){
    if (korobka_suysh_action == 1){
        yokary_gal();
        Serial.println("action1");
        if (korobka_suysh_millis + 200 < millis()){
            baseServo.write(90);
            Serial.println("action2");
        }
        if (korobka_suysh_millis + 700 < millis()){
            frontServo.write(140);
            backServo.write(150);
            Serial.println("action3");
        }
        korobka_suysh_action = 0;
    }
    //delay(200);
    //delay(500);
}

void korobka_owrul(){
    yokary_gal();
    delay(200);
    baseServo.write(90);
}

void one_goymaga_suysh(){
    backServo.write(130);
    delay(200);  
    frontServo.write(163);
}

void starting_state(){
    korobka_goyber();
    korobka_owrul();

}
void korobka_gys(){
    clawServo.write(42);
}

void korobka_goyber(){
    clawServo.write(180);  
}

void yokary_gal(){
    //long back_l = millis();
    backServo.write(10);
    delay(200);
    frontServo.write(175);
}

void sag_owrum(){
    yokary_gal();
    delay(200);
  baseServo.write(166);
  delay(500);
  one_goymaga_suysh();
}

void cep_owrum(){
    yokary_gal();
    delay(200);
  baseServo.write(20);
  delay(500);
  one_goymaga_suysh();
}

void stop_conveyer(){
    conveyMotorState = 0;
}

void start_conveyer(){
    conveyMotorState = 1;
}