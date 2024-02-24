#include <VirtualWire.h>
#include <EasyTransferVirtualWire.h>
///////////////////////////////////////
int s1 = 10;
int s2 = 9;
int s3 = 8;
int s4 = 7;
int s5 = 6;


int minPulseTime = 500; // minimum servo pulse time
int maxPulseTime = 2400; // maximum servo pulse time
int pulseTime = 0;

int pulseTime5 = 0;// Amount of time to pulse the servo
long lastPulse = 0; // the time in milliseconds of the last pulse
int refreshTime = 20;

EasyTransferVirtualWire ET; 

struct SEND_DATA_STRUCTURE{

 int p1;
 int p2; 
 int p3;
 int p4;
 int p5;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
//////////////////////////////////////////////////////////////////////

void setup(){ Serial.begin(9600);
    pinMode(s1, OUTPUT); 
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(s4, OUTPUT);
    pinMode(s5, OUTPUT);
 pulseTime = minPulseTime;



   ///////////////////////////////////////////////////////////////////////// 
  //start the library, pass in the data details
  ET.begin(details(mydata));
  
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 
  vw_set_rx_pin(11);
  vw_rx_start();  
  randomSeed(analogRead(0));
  ///////////////////////////////////////////////////////////////////////////
}

void loop(){ 
  if(ET.receiveData()){  
    Serial.print(mydata.p1);
    Serial.print("   ");
    Serial.println(mydata.p2);
    
    }
      pulseTime= map(mydata.p1,0,1023,minPulseTime,maxPulseTime);
    if (millis() - lastPulse >= refreshTime) {
 digitalWrite(s1, HIGH); // turn on pulse to the servo
 delayMicroseconds(pulseTime); // length of the pulse sets the motor position
 digitalWrite(s1, LOW); // stop pulse to the servo
 lastPulse = millis();}  

   
 pulseTime= map(mydata.p2,0,1023,minPulseTime,maxPulseTime);
    if (millis() - lastPulse >= refreshTime) {
 digitalWrite(s2, HIGH); // turn on pulse to the servo
 delayMicroseconds(pulseTime); // length of the pulse sets the motor position
 digitalWrite(s2, LOW); // stop pulse to the servo
 lastPulse = millis();}  

 
   pulseTime = map(mydata.p3,0,1023,minPulseTime,maxPulseTime);
    if (millis() - lastPulse >= refreshTime) {
 digitalWrite(s3, HIGH); // turn on pulse to the servo
 delayMicroseconds(pulseTime); // length of the pulse sets the motor position
 digitalWrite(s3, LOW); // stop pulse to the servo
 lastPulse = millis();}  

 

   pulseTime = map(mydata.p4,0,1023,minPulseTime,maxPulseTime);
    if (millis() - lastPulse >= refreshTime) {
 digitalWrite(s4, HIGH); // turn on pulse to the servo
 delayMicroseconds(pulseTime); // length of the pulse sets the motor position
 digitalWrite(s4, LOW); // stop pulse to the servo
 lastPulse = millis();}  



   pulseTime = map(mydata.p5,0,1023,minPulseTime,maxPulseTime);
    if (millis() - lastPulse >= refreshTime) {
 digitalWrite(s5, HIGH); // turn on pulse to the servo
 delayMicroseconds(pulseTime); // length of the pulse sets the motor position
 digitalWrite(s5, LOW); // stop pulse to the servo
 lastPulse = millis();}  
 
 
 
 
 }
    
  
  


