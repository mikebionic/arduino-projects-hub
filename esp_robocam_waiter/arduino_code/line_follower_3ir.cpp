int S_A = 10; //speed motor a
int M_A1 = 2; //motor a = +
int M_A2 = 3; //motor a = -
int M_B1 = 4; //motor b = -
int M_B2 = 5; //motor b = +
int S_B = 11; //speed motor b

int R_S = A0; //sincer R
int S_S = A1; //sincer S
int L_S = A2; //sincer L

void setup() {
	pinMode(M_B1, OUTPUT);
	pinMode(M_B2, OUTPUT);
	pinMode(M_A1, OUTPUT);
	pinMode(M_A2, OUTPUT);
	pinMode(S_B, OUTPUT);
	pinMode(S_A, OUTPUT);

	pinMode(L_S, INPUT);
	pinMode(S_S, INPUT);
	pinMode(R_S, INPUT);

	analogWrite(S_A, 150); 
	analogWrite(S_B, 150); 
	delay(200);
}

void loop() {
	int left_sensor_state = digitalRead(L_S);
	int right_sensor_state = digitalRead(R_S);
	int mid_sensor_state = digitalRead(S_S);

	runLineSensor();
}

void runLineSensor(){
	if (left_sensor_state == 0) && (mid_sensor_state == 1) && (right_sensor_state == 0)){
		forward();
	}
	if (left_sensor_state == 1) && (mid_sensor_state == 1) && (right_sensor_state == 0)){
		turnLeft();
	}
	if (left_sensor_state == 1) && (mid_sensor_state == 0) && (right_sensor_state == 0)){
		turnLeft();
	}
	if (left_sensor_state == 0) && (mid_sensor_state == 1) && (right_sensor_state == 1)){
		turnRight();
	}
	if (left_sensor_state == 0) && (mid_sensor_state == 0) && (right_sensor_state == 1)){
		turnRight();
	}

	if (left_sensor_state == 1) && (mid_sensor_state == 1) && (right_sensor_state == 1)){
		Stop();
	}
}




void forward(){
	digitalWrite(M_A1, LOW);
	digitalWrite(M_A2, HIGH);
	digitalWrite(M_B1, HIGH);
	digitalWrite(M_B2, LOW);  
}

void turnRight(){
	digitalWrite(M_A1, LOW);
	digitalWrite(M_A2, LOW);
	digitalWrite(M_B1, HIGH);
	digitalWrite(M_B2, LOW);  
}

void turnLeft(){
	digitalWrite(M_A1, LOW);
	digitalWrite(M_A2, HIGH);
	digitalWrite(M_B1, LOW);
	digitalWrite(M_B2, LOW);
}

void Stop(){
	digitalWrite(M_A1, LOW);
	digitalWrite(M_A2, LOW);
	digitalWrite(M_B1, LOW);
	digitalWrite(M_B2, LOW);
}