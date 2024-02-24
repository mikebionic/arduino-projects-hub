
#define ENABLE_A 6
#define MOTOR_A1 3
#define MOTOR_A2 4
 
// Define pins for Motor B
#define ENABLE_B 9
#define MOTOR_B1 8
#define MOTOR_B2 2

// Right sensor
#define TRIG_RIGHT 10
#define ECHO_RIGHT 11

// Right-center sensor
#define TRIG_MID_CTR 12
#define ECHO_MID_CTR 13

// Left sensor
#define TRIG_LEFT 4
#define ECHO_LEFT 5

/*---Helper-Function Prototypes---*/
// Motors
void disableMotors(void);
void enableMotors(void);
void goForward(void);
void goLeft(void);
void goRight(void);
void leftAvoid(void);
void rightAvoid(void);

void setupPins(void);

// Ultrasonic sensors
void doPingRight(void);
void doPingMidCtr(void);
void doPingLeft(void);
void getDistances(void);

// Obstacle avoidance
void avoidObstacles(void);

// For Ultrasonic sensor distance readings
int distance_right;
int distance_midctr;
int distance_left;
int limit = 9; // Inches, try 5-10 depending on battery strength
bool right_or_left = false; // Switch


void setup(void) {
  setupPins();
  enableMotors();
}

void loop(void) {
	getDistances();
	avoidObstacles();
}

void avoidObstacles(){
  //if (distance_midctr < limit){
  //  if (right_or_left) {
  //    rightAvoid();
  //  }
  //  else {
  //    leftAvoid();
  //  }
  //  right_or_left = !(right_or_left);
  //}


  //if(distance_left < limit) {
  //  rightAvoid();
  //}
  //else if(distance_right < limit) {
  //  leftAvoid();
  //}
  //else {
	//	goForward();
	//	delay(50);
  //}

  goForward();
}

void doPingRight() {
  /*
   * Returns the distance to the obstacle as an integer in inches
   */
  // Make the Trigger LOW (0 volts) for 2 microseconds
  digitalWrite(TRIG_RIGHT, LOW);
  delayMicroseconds(2); 
     
  // Emit high frequency 40kHz sound pulse
  // (i.e. pull the Trigger) 
  // by making Trigger HIGH (5 volts) 
  // for 10 microseconds
  digitalWrite(TRIG_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_RIGHT, LOW);
      
  // Detect a pulse on the Echo pin. 
  // pulseIn() measures the time in 
  // microseconds until the sound pulse
  // returns back to the sensor.    
  distance_right = pulseIn(ECHO_RIGHT, HIGH);
 
  // Speed of sound is:
  // 13511.811023622 inches per second
  // 13511.811023622/10^6 inches per microsecond
  // 0.013511811 inches per microsecond
  // Taking the reciprocal, we have:
  // 74.00932414 microseconds per inch 
  // Below, we convert microseconds to inches by 
  // dividing by 74 and then dividing by 2
  // to account for the roundtrip time.
  distance_right = distance_right / 74 / 2;
  distance_right = abs(distance_right);
}

void doPingMidCtr(){
  /*
   * Returns the distance to the obstacle as an integer in inches
   */
  
  // Make the Trigger LOW (0 volts) for 2 microseconds
  digitalWrite(TRIG_MID_CTR, LOW);
  delayMicroseconds(2); 
     
  // Emit high frequency 40kHz sound pulse
  // (i.e. pull the Trigger) 
  // by making Trigger HIGH (5 volts) 
  // for 10 microseconds
  digitalWrite(TRIG_MID_CTR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_MID_CTR, LOW);
      
  // Detect a pulse on the Echo pin. 
  // pulseIn() measures the time in 
  // microseconds until the sound pulse
  // returns back to the sensor.    
  distance_midctr = pulseIn(ECHO_MID_CTR, HIGH);
 
  // Speed of sound is:
  // 13511.811023622 inches per second
  // 13511.811023622/10^6 inches per microsecond
  // 0.013511811 inches per microsecond
  // Taking the reciprocal, we have:
  // 74.00932414 microseconds per inch 
  // Below, we convert microseconds to inches by 
  // dividing by 74 and then dividing by 2
  // to account for the roundtrip time.
  distance_midctr = distance_midctr / 74 / 2;
  distance_midctr = abs(distance_midctr);
}

void doPingLeft(){
  /*
   * Returns the distance to the obstacle as an integer in inches
   */

  // Make the Trigger LOW (0 volts) for 2 microseconds
  digitalWrite(TRIG_LEFT, LOW);
  delayMicroseconds(2); 
     
  // Emit high frequency 40kHz sound pulse
  // (i.e. pull the Trigger) 
  // by making Trigger HIGH (5 volts) 
  // for 10 microseconds
  digitalWrite(TRIG_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_LEFT, LOW);
      
  // Detect a pulse on the Echo pin. 
  // pulseIn() measures the time in 
  // microseconds until the sound pulse
  // returns back to the sensor.    
  distance_left = pulseIn(ECHO_LEFT, HIGH);
 
  // Speed of sound is:
  // 13511.811023622 inches per second
  // 13511.811023622/10^6 inches per microsecond
  // 0.013511811 inches per microsecond
  // Taking the reciprocal, we have:
  // 74.00932414 microseconds per inch 
  // Below, we convert microseconds to inches by 
  // dividing by 74 and then dividing by 2
  // to account for the roundtrip time.
  distance_left = distance_left / 74 / 2;
  distance_left = abs(distance_left); 
}

void getDistances() {
  // Take distance readings on the HC-SR04
  doPingRight();
  doPingMidCtr();  
  doPingLeft();   
}

void disableMotors(){
  digitalWrite(ENABLE_A, LOW);
  digitalWrite(ENABLE_B, LOW);
}

void enableMotors(){
  digitalWrite(ENABLE_A, HIGH);
  digitalWrite(ENABLE_B, HIGH);  
}

void goForward(){
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

void goLeft(){
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite (MOTOR_B2, LOW);
}

void goRight(){
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

void leftAvoid(){
  // Go to the left when an object is detected
  // on the right-side of the vehicle
  while((distance_right < limit) || (distance_midctr < limit)) {
    goLeft();
    delay(4);
    doPingRight();
    doPingMidCtr();
  }
  goForward();

}


void rightAvoid(){
  while((distance_left < limit) || (distance_midctr < limit)) {
    goRight();
    delay(4);
    doPingLeft();
    doPingMidCtr();
  }
  goForward();
}

void setupPins(){
  // Configure motor pins
  pinMode(ENABLE_A, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);    
  pinMode(ENABLE_B, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);  

  // Configure HC-SR04 pins
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_MID_CTR, OUTPUT);
  pinMode(ECHO_MID_CTR, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
}