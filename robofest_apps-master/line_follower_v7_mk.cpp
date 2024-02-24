
int left_most_Sensor = A4;
int leftSensor = A3;
int left_close_Sensor = 9;
int midSensor = A2;
int right_close_Sensor = 8;
int rightSensor = A1;
int right_most_Sensor = A0;

char data[100];
String sensorsData = "0000000";
String thisTurn = "forward";

int maxSpeed = 255;
int midSpeed = 255 - 100;
int slowSpeed = 255 - 170;
int super_slowSpeed = 255 - 190;

// Motors
#define sag1 2
#define sag2 3
#define cep1 4
#define cep2 7
#define right_en 5
#define left_en 6

int sag1_state = 0;
int sag2_state = 0;
int cep1_state = 0;
int cep2_state = 0;
// Motors

void setup() {
    Serial.begin(9600);
    pinMode(sag1, OUTPUT);
    pinMode(sag2, OUTPUT);
    pinMode(cep1, OUTPUT);
    pinMode(cep2, OUTPUT);
    pinMode(right_en, OUTPUT);
    pinMode(left_en, OUTPUT);

    pinMode(left_most_Sensor, INPUT);
    pinMode(leftSensor, INPUT);
    pinMode(left_close_Sensor, INPUT);
    pinMode(midSensor, INPUT);
    pinMode(right_close_Sensor, INPUT);
    pinMode(rightSensor, INPUT);
    pinMode(right_most_Sensor, INPUT);

    //analogWrite(right_en, slowSpeed);
    //analogWrite(left_en, slowSpeed);
}


void loop(){
  //updateColorValues();
  calculate_and_run2();

  //forward();
	//analogWrite(left_en, midSpeed);
	//analogWrite(right_en, super_slowSpeed);

  digitalWrite(sag1,sag1_state);
  digitalWrite(sag2,sag2_state);
  digitalWrite(cep1,cep1_state);
  digitalWrite(cep2,cep2_state);
}

//void updateColorValues(){

//    sprintf(data, "%d%d%d%d%d%d%d",
//        !digitalRead(left_most_Sensor),
//        !digitalRead(leftSensor),
//        digitalRead(left_close_Sensor),
//        !digitalRead(midSensor),
//        digitalRead(right_close_Sensor),
//        !digitalRead(rightSensor),
//        !digitalRead(right_most_Sensor)
//    );
//    sensorsData = String(data);

//    Serial.print("Turn: __ ");
//    Serial.print(thisTurn);
//    Serial.print("     ");
//    Serial.print(sensorsData == "0010000");
//    Serial.print("    __  DATA:  ");
//    Serial.println(sensorsData);
//}

void calculate_and_run2(){
	if(
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 1
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0

			//sensorsData == "0010000"
	){
		//Serial.println("sensorsData == 0010000");
		forward();
		thisTurn = "forward_left";
		analogWrite(left_en, slowSpeed);
		analogWrite(right_en, midSpeed);
	}
	else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 1
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "0000100"
	){
		//Serial.println("sensorsData == 0000100");
		forward();
		thisTurn = "forward_right";
		analogWrite(left_en, midSpeed);
		analogWrite(right_en, slowSpeed);
	}
	else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 1
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "0001000" 
	) {
		thisTurn = "forward";
		forward();
		analogWrite(left_en, midSpeed);
		analogWrite(right_en, midSpeed);
	}

  else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 1
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "0100000"
	){
		//Serial.println("sensorsData == 0100000");
    thisTurn = "left";
    left_slow();
		//forward();
    analogWrite(left_en, super_slowSpeed);
    analogWrite(right_en, midSpeed);
  }

  else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 1
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "0000010"
	){
		//Serial.println("sensorsData == 0000010");
    thisTurn = "right";
    right_slow();
		//forward();
    analogWrite(left_en, midSpeed);
    analogWrite(right_en, super_slowSpeed);
  }

  else if(
		
		!digitalRead(left_most_Sensor) == 1
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "1000000"
	){
		//Serial.println("sensorsData == 1000000");
    thisTurn = "left";
    left();
    //left_slow();
		analogWrite(left_en, slowSpeed);//super_slowSpeed
    analogWrite(right_en, slowSpeed);
  }

  else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
			&&
		digitalRead(left_close_Sensor) == 0
			&&
		!digitalRead(midSensor) == 0
			&&
		digitalRead(right_close_Sensor) == 0
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 1
		
		//sensorsData == "0000001"
	){
		//Serial.println("sensorsData == 0000001");
    thisTurn = "right";
    right();
    //right_slow();
		analogWrite(left_en, slowSpeed);
    analogWrite(right_en, slowSpeed);//super_slowSpeed
  }

	//else if(sensorsData == "1100000"){
	//	//Serial.println("sensorsData == 1100000");
	//  thisTurn = "left";
	//  //left();
	//  left_slow();
	//	analogWrite(left_en, super_slowSpeed);
	//  analogWrite(right_en, slowSpeed);
	//}
	//else if(sensorsData == "0000011"){
	//	//Serial.println("sensorsData == 0000011");
	//  thisTurn = "right";
	//  //right();
	//  right_slow();
	//	analogWrite(left_en, slowSpeed);
	//  analogWrite(right_en, super_slowSpeed);
	//}

	//else if(sensorsData == "0110000"){
	//	//Serial.println("sensorsData == 0110000");
	//  thisTurn = "left";
	//  //left();
	//	left_slow();
	//  analogWrite(left_en, slowSpeed);
	//  analogWrite(right_en, slowSpeed);
	//}
	//else if(sensorsData == "0000110"){
	//	//Serial.println("sensorsData == 0000110");
	//  thisTurn = "right";
	//  //right();
	//	right_slow();
	//  analogWrite(left_en, slowSpeed);
	//  analogWrite(right_en, slowSpeed);
	//}


	//else if(sensorsData == "0011000"){
	//	//Serial.println("sensorsData == 0011000");
	//  thisTurn = "left_slow";
	//  //left_slow();
	//	forward();
	//  //analogWrite(left_en, midSpeed);
	//  //analogWrite(right_en, midSpeed);
	//	analogWrite(left_en, slowSpeed);
	//	analogWrite(right_en, midSpeed);
	//}
	//else if(sensorsData == "0001100"){
	//	//Serial.println("sensorsData == 0001100");
	//  thisTurn = "right_slow";
	//  //right_slow();
	//	forward();
	//  //analogWrite(left_en, midSpeed);
	//  //analogWrite(right_en, midSpeed);

	//	analogWrite(left_en, midSpeed);
	//	analogWrite(right_en, slowSpeed);
	//}

	//else if(sensorsData == "0011100"){
	//	//Serial.println("sensorsData == 0011100");
	//  thisTurn = "forward";
	//  forward();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}
	//else if(sensorsData == "0001110"){
	//	//Serial.println("sensorsData == 0001110");
	//  thisTurn = "right_slow";
	//  right_slow();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}
	//else if(sensorsData == "0111000"){
	//	//Serial.println("sensorsData == 0111000");
	//  thisTurn = "left_slow";
	//  left_slow();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}

	//else if(sensorsData == "0000111"){
	//	//Serial.println("sensorsData == 0000111");
	//  thisTurn = "right";
	//  right();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}
	//else if(sensorsData == "1110000"){
	//	//Serial.println("sensorsData == 1110000");
	//  thisTurn = "left";
	//  left();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}


	//else if(sensorsData == "0001111"){
	//	//Serial.println("sensorsData == 0001111");
	//  thisTurn = "right";
	//  right();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}
	//else if(sensorsData == "1111000"){
	//	//Serial.println("sensorsData == 1111000");
	//  thisTurn = "left";
	//  left();
	//  analogWrite(left_en, midSpeed);
	//  analogWrite(right_en, midSpeed);
	//}



  else if(
		
		!digitalRead(left_most_Sensor) == 1
			&&
		!digitalRead(leftSensor) == 1
		//	&&
		//digitalRead(left_close_Sensor) == 1
		//	&&
		//!digitalRead(midSensor) == 0
		// 	&&
		// (digitalRead(right_close_Sensor) == 0 || digitalRead(right_close_Sensor) == 1)
			&&
		!digitalRead(rightSensor) == 0
			&&
		!digitalRead(right_most_Sensor) == 0
		
		//sensorsData == "1000000"
	){
		//Serial.println("sensorsData == 1000000");
    thisTurn = "left";
    left();
    //left_slow();
		analogWrite(left_en, slowSpeed);//super_slowSpeed
    analogWrite(right_en, slowSpeed);
  }

  else if(
		
		!digitalRead(left_most_Sensor) == 0
			&&
		!digitalRead(leftSensor) == 0
		// 	&&
		// digitalRead(left_close_Sensor) == 0
		//	&&
		//!digitalRead(midSensor) == 0
		//	&&
		//digitalRead(right_close_Sensor) == 1
			&&
		!digitalRead(rightSensor) == 1
			&&
		!digitalRead(right_most_Sensor) == 1
		
		//sensorsData == "0000001"
	){
		//Serial.println("sensorsData == 0000001");
    thisTurn = "right";
    right();
    //right_slow();
		analogWrite(left_en, slowSpeed);
    analogWrite(right_en, slowSpeed);//super_slowSpeed
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