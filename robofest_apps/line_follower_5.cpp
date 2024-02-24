#define INA_2 10 //This is the left forward control of the robot, I defined each pwm 
pin that is connected to the arduino 
#define INB_2 11 //This is the left backward control of the motor, e.g set this high and 
INB_1 high and others low you will do a reverse 
#define INA_1 5 //This is the right forward control of the motor 
#define INB_1 6 //This is the right backward control of the motor 

void setup() 
{ // This is always the 1st void function in an arduino program 

Serial.begin(9600); 

pinMode(INA_2, OUTPUT); //each pwm pin was placed as an output for the 

//program 
pinMode(INB_2, OUTPUT); 
pinMode(INA_1, OUTPUT); 
pinMode(INB_1, OUTPUT); 

} 

void loop() { //This is a loop shows the sensor and the driver funtion 

sensor(); 

driver(); 

} 

void driver() //This is the driver function, it reads the sensors and drives the motor 
using pwm signal 

{ 

int lowVal = 60; // i did set my sensor low value to be 60 note this is not the 
//lowest value the sensor can go 

int highVal = 300; // i did set my sensor high value to be 300 note this is not the 
//highest value the sensor can go 

int s0 = analogRead(A0); //This defines the sensor value s0, it puts the reading of 
analogread(A0) into s0 

int s1 = analogRead(A1); 

int s2 = analogRead(A2); 

int s3 = analogRead(A3); 

int s4 = analogRead(A4); 

int s5 = analogRead(A5); 

//////////////////////////////////////////////// 

if ((s2 >= highVal) && (s3 >= highVal)) //This is the 1st if statement of the program, 
it says if s2 and s3 see's a black line robot should move straight at highest speed 

{ 
analogWrite(INA_2, 255); 
analogWrite(INB_2, 0); 
analogWrite(INA_1, 255); 
analogWrite(INB_1, 0); 

} 

else if ((s3 >= highVal) && (s4 >= highVal)) 

{ 
analogWrite(INA_2, 200); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,240); 
analogWrite(INB_1, 0); 

} 

else if ((s4 >= highVal) && (s5 >= highVal)) 

{ 
analogWrite(INA_2, 0); 
analogWrite(INB_2, 0); 
analogWrite(INA_1, 200); 
analogWrite(INB_1, 0); 

} 

else if((s1 >= highVal) && (s2 >= highVal)) 

{ 
analogWrite(INA_2, 200); 
analogWrite(INB_2, 0); 
analogWrite(INA_1, 255); 
analogWrite(INB_1, 0); 

} 

else if ((s0 >= highVal) && (s1 >= highVal)) 

{ 
analogWrite(INA_2, 200); 
analogWrite(INB_2, 0); 
analogWrite(INA_1, 0); 
analogWrite(INB_1, 0); 

} 

else if(s0 >= highVal) 

{ 
analogWrite(INA_2, 200); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,0); 
analogWrite(INB_1, 0); 

} 

else if(s1 >= highVal) 

{ 
analogWrite(INA_2, 200); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,0); 
analogWrite(INB_1, 0); 

} 

else if(s2 >= highVal) 

{ 
analogWrite(INA_2, 255); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,255); 
analogWrite(INB_1, 0); 

} 

else if(s3 >= highVal) 

{ 
analogWrite(INA_2, 255); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,255); 
analogWrite(INB_1, 0); 

} 

else if(s4 >= highVal) 

{ 
analogWrite(INA_2, 0); 
analogWrite(INB_2, 0); 
analogWrite(INA_1, 200); 
analogWrite(INB_1, 0); 

} 

else if(s5 >= highVal) 

{ 
analogWrite(INA_2, 0); 
analogWrite(INB_2, 0); 
analogWrite(INA_1,200); 
analogWrite(INB_1, 0); 

} 

else if((s0 <= lowVal) && (s1 <= lowVal) && (s2 <= lowVal) && (s3 <= lowVal) 
&& (s4 <= lowVal) && (s5 <= lowVal)) //This says if its all white light the robot should make a 180 degree left turn 

{ 
analogWrite(INA_2, 0); 
analogWrite(INB_2, 200); 
analogWrite(INA_1,200); 
analogWrite(INB_1, 0); 

} 

} 

void sensor(){ //This function basically prints the sensor reading so you can see 
what sensors are working. 
int s0 = analogRead(A0); 
int s1 = analogRead(A1); 
int s2 = analogRead(A2); 
int s3 = analogRead(A3); 
int s4 = analogRead(A4); 
int s5 = analogRead(A5); 

Serial.print("s0 "); //This prints out the reading for each sensor 
Serial.print(s0); 
Serial.print(" s1 "); 
Serial.print(s1); 
Serial.print(" s2 "); 
Serial.print(s2); 
Serial.print(" s3 "); 
Serial.print(s3); 
Serial.print(" s4 "); 
Serial.print(s4); 

Serial.print(" s5 "); 

Serial.print(s5); 

Serial.print(' '); 

Serial.println(); 
}