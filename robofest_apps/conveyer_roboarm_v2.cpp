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
int robot_arm_running = 0;

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
    //sag_owrum();
    //yokary_gal();
    //delay(1000);
    //sag_owrum();
    starting_state();
    delay(1000);


}

void run_robo_arm(){
    Serial.print("+++++++++++++ IR value is :");
    Serial.println(inIrSensor_value_saved);
    stop_conveyer();
    robot_arm_running = 1;
    korobka_suysh();
    out_box_millis = millis();
    delay(500);
    out_box_millis = millis();
    korobka_gys();
    out_box_millis = millis();
    delay(500);
    out_box_millis = millis();
    if (inIrSensor_value_saved == 0){
        cep_owrum();
    } else {
        sag_owrum();
    }
    out_box_millis = millis();
    korobka_goyber();
    out_box_millis = millis();
    delay(500);
    yokary_gal();
    out_box_millis = millis();
    delay(200);
    korobka_gys();
    out_box_millis = millis();
    delay(200);
    one_goymaga_suysh();
    out_box_millis = millis();
    delay(200);
    korobka_goyber();
    out_box_millis = millis();
    delay(400);
    out_box_millis = millis();
    starting_state();
    robot_arm_running = 0;
    out_box_detected = 0;
    boxDetected = 0;
}


void readIrSensors(){
    inIrSensor_value = digitalRead(inIrSensor);
    outIrSensor_value = digitalRead(outIrSensor);
}

void inSonicHandler(){
	if (boxDetected == 0){
		if (inSonicDist < inSonicThresh){
            Serial.println("IN Sonic Is DETECTED");
               inIrSensor_value_saved = inIrSensor_value;
            //long x;
            //if (inIrSensor_value == 1){
            //    x = millis();
            //    inIrSensor_value_saved = 1;
            //}
            //if (x+1000 < millis()){
            //    //i
            //   inIrSensor_value_saved = inIrSensor_value;
            //}
            boxDetected = 1;
		}
	}
}


void readUltrasonics(){
    outSonicDist = outSonic.Ranging(CM);
    inSonicDist = inSonic.Ranging(CM);

    Serial.print("                                            conveyer: ___ ");
    Serial.println(conveyMotorState);
    Serial.print("ultrasonicsss ___ ");
    Serial.print(inSonicDist);
    Serial.print("    ___    ");
    Serial.println(outSonicDist);
}


void loop(){
    //run_robo_arm();
    if (robot_arm_running){
        out_box_millis = millis();
    }
    //boxGate.write(boxGate_openedVal);

    //if inIrSensor_value_saved == 1 -> Black box
    //if inIrSensor_value_saved == 0 -> white box
    if (Serial.available() > 0){
        stream = Serial.read();
        if (stream == '1'){
            korobka_suysh();
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
        Serial.println("boxDetected == 1");
        if (outSonicDist < outSonicThresh){
            Serial.println("outSonicDist < outSonicThresh");

            stop_conveyer();
            out_box_detected = 1;
            out_box_millis = millis();
            Serial.println("outSonicDist < outSonicThresh out_box_millis = millis()");
        }
    }
    if (out_box_detected){
        stop_conveyer();
        Serial.println("if (out_box_detected)");
        if (outSonicDist < outSonicThresh){
            Serial.println("if (out_box_detected) outSonicDist < outSonicThresh");
            out_box_millis = millis();
            run_robo_arm();
        }

        //if (out_box_millis + 3000 < millis()){
        //    if (!(outSonicDist < outSonicThresh)){
        //        out_box_detected = 0;
        //        boxDetected = 0;
        //    }
        //}
    }

    if (boxDetected == 0){
        if (!(inSonicDist < inSonicThresh)){
            stop_conveyer();
            closeGate();
            openChannel();
        }
        inSonicHandler();
    }
    else if (boxDetected == 1 && out_box_detected == 0 && robot_arm_running == 0){
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


void korobka_suysh(){
    yokary_gal();
    delay(200);
    baseServo.write(92);
    delay(200);
    frontServo.write(130);
    backServo.write(148);
}

void korobka_owrul(){
    yokary_gal();
    delay(200);
    baseServo.write(92);
    delay(200);
}

void one_goymaga_suysh(){
    backServo.write(105);
    delay(200);
    frontServo.write(143);
    delay(200);
}

void starting_state(){
    korobka_goyber();
    korobka_owrul();

}
void korobka_gys(){
    clawServo.write(10);
    delay(100);
}

void korobka_goyber(){
    clawServo.write(160);
    delay(100);
}

void yokary_gal(){
    backServo.write(70);
    delay(200);
    frontServo.write(157);
}

void sag_owrum(){
    yokary_gal();
    delay(400);
    baseServo.write(164);
    delay(800);
    one_goymaga_suysh();
    delay(400);
}

void cep_owrum(){
    yokary_gal();
    delay(400);
    baseServo.write(24);
    delay(800);
    one_goymaga_suysh();
    delay(400);
}

void stop_conveyer(){
    conveyMotorState = 0;
    digitalWrite(conveyMotor, conveyMotorState);
}

void start_conveyer(){
    conveyMotorState = 1;
    digitalWrite(conveyMotor, conveyMotorState);
}