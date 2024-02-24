#include <Servo.h>
#include "Ultrasonic.h"

Servo clawServo;
Servo frontServo;
Servo backServo;
Servo baseServo;

Ultrasonic outSonic(12,13);
int outSonicDist;
Ultrasonic inSonic(10,11);
int inSonicDist;
int inSonicThresh = 4;
int outSonicThresh = 12;
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

Servo boxChannel;
Servo boxGate;

int conveyMotor = 8;
int conveyMotorState = 0;

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
    // cep_owrum();
    // korobka_gys();
//    digitalWrite(conveyMotor,1);

// yokary_gal();
// sag_owrum();
}


void readIrSensors(){
    inIrSensor_value = digitalRead(inIrSensor);
    outIrSensor_value = digitalRead(outIrSensor);
    if (inSonicDist < inSonicThresh){
        inIrSensor_value_saved = inIrSensor_value;
        Serial.print("+++++++++++ ==== New IR sensor value:  ");
        Serial.println(inIrSensor_value_saved);
        continue_after_value_save = 1;
        Serial.print("SSSSSSSSSSSSSAAAAAAAAAAAAVEEED");
        Serial.println(continue_after_value_save);
    }
}

void control_conveyer_after_read(){
    if (continue_after_value_save == 1){
        release_box_servo();
        start_conveyer();
        continue_after_value_save = 0;
    }
    if (prepare_after_box_done == 1){
        prepare_box_servo();
        stop_conveyer();
        prepare_after_box_done = 0;
    }
}

void readUltrasonics(){
    outSonicDist = outSonic.Ranging(CM);
    inSonicDist = inSonic.Ranging(CM);

    Serial.print("Ulrasonicsssss +++ ");
    Serial.print(inSonicDist);
    Serial.print("    ______     ");
    Serial.println(outSonicDist);
    Serial.print("ConveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeYYY ___ ");
    Serial.println(conveyMotorState);

    if (outSonicDist < outSonicThresh){
        stop_conveyer();
        box_is_out = 1;
        box_released_mode = 0;
        // other functions to get box
    } else {
        if (box_is_out == 1){
            // release_box_servo();
            prepare_after_box_done = 1;
            box_is_out = 0;
            // start_conveyer();
        }

    }
}


void loop(){

    // if outSonic detect
    // stop conveyer
    // send value that box is out

    // // else 
    // // box not out

    // when out sonic release
    // if box is out value true
    //     close gate
    //     open channel
    //     readsonic and color
    // else close gate openchannel

    // remember color
    // open gate
    // run conveyer
    readUltrasonics();
    readIrSensors();
    digitalWrite(conveyMotor, conveyMotorState);
    box_in_ready_handler();
    control_conveyer_after_read();
//   korobka_suysh();
//   delay(2000);
//   korobka_gys();
//   delay(2000);
//   yokary_gal();
//   delay(2000);
//   sag_owrum();
//   delay(2000);
//   korobka_goyber();
//   delay(2000);


}

void prepare_box_servo(){
    boxChannel.write(boxChannel_openedVal);
    boxGate.write(boxGate_closedVal);
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

void korobka_suysh(){
    baseServo.write(90);
    delay(80);
    delay(500);
    frontServo.write(140);
    delay(80);
    backServo.write(150);
    delay(80);
}

void korobka_gys(){
    clawServo.write(45);
    delay(80);
}

void korobka_goyber(){
    clawServo.write(180);
    delay(80);  
}

void yokary_gal(){
    frontServo.write(150);
    delay(80);
    backServo.write(80);
    delay(80);  
}

void sag_owrum(){
  baseServo.write(160);
  delay(80);
}

void cep_owrum(){
  baseServo.write(20);
  delay(80);
}

void stop_conveyer(){
    conveyMotorState = 0;
    digitalWrite(conveyMotor, conveyMotorState);
}

void start_conveyer(){
    conveyMotorState = 1;
    digitalWrite(conveyMotor, conveyMotorState);
}