// ultrasonic
#define echoPin 8
#define trigPin 9
long duration;
int distance;
int minDistance = 40;
int backwardDistance = 80;
int stopTime = 5000;

int backwardMode = 0;
int midConnect = "3";

// motor
int S_A = 10;  //speed motor a
int M_A1 = 2; //motor a = +
int M_A2 = 3; //motor a = -
int M_B1 = 4; //motor b = -
int M_B2 = 5; //motor b = +
int S_B = 11;  //speed motor b

int R_S = A0; //sincer R
int S_S = A1; //sincer S
int L_S = A2; //sincer L

int reverseMode = 0;

void setup() {
	// ultrasonic
	pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
	// ultrasonic

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
		// Stop();
		if (midConnect == "3"){
			if (backwardMode == 1){
				turnRight();
			} else {
				turnLeft();
			}
			delay(1000);
			forward();
			delay(1000);
		}
		if (midConnect == "2"){
			forward();
			delay(1000);
			forward();
			delay(1000);
		}
		if (midConnect == "1"){
			if (backwardMode == 1){
				turnLeft();
			} else {
				turnRight();
			}
			delay(1000);
			forward();
			delay(1000);
		}
		//configure mid connect
	}
}


void forward(){
	if (distance > minDistance) {
		digitalWrite(M_A1, 0);
		digitalWrite(M_A2, 1);
		digitalWrite(M_B1, 1);
		digitalWrite(M_B2, 0);
	}
}

void backward(){
	digitalWrite(M_A1, 1);
	digitalWrite(M_A2, 0);
	digitalWrite(M_B1, 0);
	digitalWrite(M_B2, 1);
}

void turnRight(){
	if (distance > minDistance) {
		digitalWrite(M_A1, 0);
		digitalWrite(M_A2, 0);
		digitalWrite(M_B1, 1);
		digitalWrite(M_B2, 0);
	}
}

void turnLeft(){
	if (distance > minDistance) {
		digitalWrite(M_A1, 0);
		digitalWrite(M_A2, 1);
		digitalWrite(M_B1, 0);
		digitalWrite(M_B2, 0);
	}
}

void Stop(){
	digitalWrite(M_A1, 0);
	digitalWrite(M_A2, 0);
	digitalWrite(M_B1, 0);
	digitalWrite(M_B2, 0);
}

void readUltrasonicSensor() {
	digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  duration = pulseIn(echoPin, 1);
  distance = duration * 0.034 / 2;
	if (distance < minDistance) {
		Stop();
		delay(stopTime);
		turnAround();
		delay(2000);
	}
	turnAroundTillLine();
}


void turnAroundTillLine(){
	backwardMode = 1;
	if (left_sensor_state == 0) && (mid_sensor_state == 0) && (right_sensor_state == 0)){
		turnAround();
	}
}

void turnAround(){
	digitalWrite(M_A1, 1);
	digitalWrite(M_A2, 0);
	digitalWrite(M_B1, 1);
	digitalWrite(M_B2, 0);
}