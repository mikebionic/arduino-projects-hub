
#define ENABLE_A 5
#define MOTOR_A1 6
#define MOTOR_A2 4
 
// Define pins for Motor B
#define ENABLE_B 8
#define MOTOR_B1 7
#define MOTOR_B2 9

// Right sensor
#define TRIG_RIGHT A2
#define ECHO_RIGHT A1

// Right-center sensor
#define TRIG_RIGHT_CTR 12
#define ECHO_RIGHT_CTR 13

// Left-center sensor
#define TRIG_LEFT_CTR 10
#define ECHO_LEFT_CTR 11

// Left sensor
#define TRIG_LEFT 3
#define ECHO_LEFT 2

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
void doPingRightCtr(void);
void doPingLeftCtr(void);
void doPingLeft(void);
void getDistances(void);

// Obstacle avoidance
void avoidObstacles(void);

// For Ultrasonic sensor distance readings
int distance_right;
int distance_rightctr;
int distance_leftctr;
int distance_left;
int limit = 9; // Inches, try 5-10 depending on battery strength
bool right_or_left = false; // Switch


void setup(void) {
  setupPins();
  enableMotors();
}

void loop(void) {
  //// Stage 0 - before the robot enters the 
  //// multi-obstacle environment 
  //while(!crossed_the_tape) {

  //  delay(50);
    
  //  // Read desired heading
  //  sensors_event_t event;
  //  bno.getEvent(&event);
  //  desired_heading = event.orientation.x;
    
  //  goForward();
    
  //  readIRSensor();
  //}

  //crossed_the_tape = false;

  //// Stage 1
  //while(!crossed_the_tape) {

  //  // Read all four HC-SR04 sensors
  //  getDistances();

  //  // Avoid any obstacle along the way
  //  avoidObstacles();
  //}

  //heading_threshold = 10;
  
  //// Capture the time
  //start_time = millis();

  //// Stage 2
  //while(!done) {

  //  calculateHeadingError();

  //  // Correct the heading if needed
  //  if (abs(heading_error) <= abs(heading_threshold)){
  //    goForward();
  //  }
  //  else {
  //    correctHeading();
  //    goForward();
  //  }

  //  // Check to see if we are done
  //  if (((millis()) - start_time) > time_elapsed_threshold) {
  //    done = true;
  //  }
  //}



	getDistances();
	avoidObstacles();
  
  //while(done) {
  //  disableMotors();
  //  delay(1000);
  //}

}

void avoidObstacles(){
  // Avoid any objects
  if ((distance_leftctr < limit) && (distance_rightctr < limit)){
    // Switch back and forth
    if (right_or_left) {
      rightAvoid();
    }
    else {
      leftAvoid();
    }
    right_or_left = !(right_or_left);
  }
  else if((distance_left < limit) || (distance_leftctr < limit)) {
    rightAvoid();
  }
  else if((distance_right < limit) || (distance_rightctr < limit)) {
    leftAvoid();
  }
  else {
		goForward();
		delay(50);
  }
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

void doPingRightCtr(){
  /*
   * Returns the distance to the obstacle as an integer in inches
   */
  
  // Make the Trigger LOW (0 volts) for 2 microseconds
  digitalWrite(TRIG_RIGHT_CTR, LOW);
  delayMicroseconds(2); 
     
  // Emit high frequency 40kHz sound pulse
  // (i.e. pull the Trigger) 
  // by making Trigger HIGH (5 volts) 
  // for 10 microseconds
  digitalWrite(TRIG_RIGHT_CTR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_RIGHT_CTR, LOW);
      
  // Detect a pulse on the Echo pin. 
  // pulseIn() measures the time in 
  // microseconds until the sound pulse
  // returns back to the sensor.    
  distance_rightctr = pulseIn(ECHO_RIGHT_CTR, HIGH);
 
  // Speed of sound is:
  // 13511.811023622 inches per second
  // 13511.811023622/10^6 inches per microsecond
  // 0.013511811 inches per microsecond
  // Taking the reciprocal, we have:
  // 74.00932414 microseconds per inch 
  // Below, we convert microseconds to inches by 
  // dividing by 74 and then dividing by 2
  // to account for the roundtrip time.
  distance_rightctr = distance_rightctr / 74 / 2;
  distance_rightctr = abs(distance_rightctr);
}

void doPingLeftCtr(){
  /*
   * Returns the distance to the obstacle as an integer in inches
   */

  // Make the Trigger LOW (0 volts) for 2 microseconds
  digitalWrite(TRIG_LEFT_CTR, LOW);
  delayMicroseconds(2); 
     
  // Emit high frequency 40kHz sound pulse
  // (i.e. pull the Trigger) 
  // by making Trigger HIGH (5 volts) 
  // for 10 microseconds
  digitalWrite(TRIG_LEFT_CTR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_LEFT_CTR, LOW);
      
  // Detect a pulse on the Echo pin. 
  // pulseIn() measures the time in 
  // microseconds until the sound pulse
  // returns back to the sensor.    
  distance_leftctr = pulseIn(ECHO_LEFT_CTR, HIGH);
 
  // Speed of sound is:
  // 13511.811023622 inches per second
  // 13511.811023622/10^6 inches per microsecond
  // 0.013511811 inches per microsecond
  // Taking the reciprocal, we have:
  // 74.00932414 microseconds per inch 
  // Below, we convert microseconds to inches by 
  // dividing by 74 and then dividing by 2
  // to account for the roundtrip time.
  distance_leftctr = distance_leftctr / 74 / 2;
  distance_leftctr = abs(distance_leftctr);
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
  doPingLeftCtr();
  doPingRightCtr();  
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
  while((distance_right < limit) || (distance_rightctr < limit)) {
    goLeft();
    delay(4);
    doPingRight();
    doPingRightCtr();
  }
  goForward();

}


void rightAvoid(){
  while((distance_left < limit) || (distance_leftctr < limit)) {
    goRight();
    delay(4);
    doPingLeft();
    doPingLeftCtr();
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
  pinMode(TRIG_RIGHT_CTR, OUTPUT);
  pinMode(ECHO_RIGHT_CTR, INPUT);
  pinMode(TRIG_LEFT_CTR, OUTPUT);
  pinMode(ECHO_LEFT_CTR, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
}