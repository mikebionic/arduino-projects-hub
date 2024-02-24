#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float dht_humi;
unsigned int dht_temp;

Servo cyglyk_s;
Servo motor_s;

int slow_servo_state = 0;
int setted_slow_servo_state = 0;
long slow_servo_millis;
int slow_servo_speed = 20;


int motor_turn_time_h = 2;
long motor_turn_time_ms = 10800000; ///2 * 60 * 60 * 1000;

const int c_s_pin = 4;
const int m_s_pin = 5;
const int fan_pin = 6;
const int lmp_pin = 7;
const int pot_pin = A0;
const int sbtn_pin= 12;

int pot_val;
int setted_T;
long temp_millis;
long motor_millis;

int motor_s_down_val = 165;
int motor_s_up_val = 15;
int cyglyk_s_down_val = 179;
int cyglyk_s_up_val = 1;
int motor_current_state = 1;

byte u[8] = 
{
  0b01010,
  0b00000,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b01101,
  0b00000
};

void setup() {
    Serial.begin(9600);
    dht.begin();
    
    //-----LCD------
    lcd.begin();
    lcd.backlight();
    lcd.createChar(1,u);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Salam!!");
    lcd.setCursor(0,1);
    lcd.print("Zayebal ;)");
    
    //-----PINS-----
    pinMode(fan_pin,OUTPUT);
    pinMode(lmp_pin,OUTPUT);
    pinMode(pot_pin,INPUT);
    pinMode(sbtn_pin,INPUT);
    
    cyglyk_s.attach(c_s_pin);
    motor_s.attach(m_s_pin);

    //checking the motor
    cyglyk_s.write(cyglyk_s_down_val);
    delay(500);
    cyglyk_s.write(cyglyk_s_up_val);
    delay(500);
    cyglyk_s.write(cyglyk_s_down_val);
    delay(1000);
    lcd.clear();
}


void loop() {
    temp();
    temp_sazlayjy();
    humidity_controller();
    motor_s_turning();
    servo_write_slow();    
    sbtn_motor_manual_control();
}


// collect temperature info from sensor
void temp(){
    if ((temp_millis + 4000) < millis()){ 
        dht_humi = dht.readHumidity();
        dht_temp = dht.readTemperature();

        lcd.setCursor(0,0);
        lcd.print ("Tmp ");
        lcd.print (dht_temp);
        lcd.print ("*C   ");
        lcd.setCursor (0,1);
        lcd.print ("Cyg ");
        lcd.print (dht_humi);
        lcd.print ("%");
        lcd.setCursor (7,1);
        lcd.print ("     ");
        Serial.print ("Temp = ");
        Serial.print (dht_temp);
        Serial.print (" *C ");
        Serial.print ("Cyglylyk ");
        Serial.print (dht_humi);
        Serial.println (" %");
        temp_millis = millis();
    }
}


// Control the temperature by switching heater on/off
void temp_sazlayjy() {
    pot_val = analogRead(pot_pin);
    setted_T = map(pot_val,0,1023,30,41);
    lcd.setCursor(9,0);

    // printing the elapsed time to turn the holder
    lcd.print(((motor_millis + motor_turn_time_ms) - millis())/1000);
    lcd.print("        ");
    lcd.setCursor(12,1);
    lcd.print(setted_T);
    lcd.print("*C  ");
    Serial.println(setted_T);
    if (setted_T > dht_temp ) {
        digitalWrite(lmp_pin, 0);
    } else if (setted_T < dht_temp) {
        digitalWrite(lmp_pin, 1);
    } 
}


// Control the humidity with servo and fan
void humidity_controller(){
    if (dht_humi > 50) {
        cyglyk_s.write (cyglyk_s_up_val);
        digitalWrite(fan_pin, 1);
    }
    else{
        cyglyk_s.write(cyglyk_s_down_val);
        digitalWrite(fan_pin, 0);
    }
}


void motor_s_turning() {
    if((motor_millis + motor_turn_time_ms) < millis()){
        if (motor_current_state == 1){
            // motor_s.write(motor_s_up_val);
            setted_slow_servo_state = motor_s_up_val;
            motor_current_state = 0;
        } else {
            setted_slow_servo_state = motor_s_down_val;
            motor_current_state = 1;
        }
        motor_millis = millis();
    }
}


void servo_write_slow(){
  if (slow_servo_state <= setted_slow_servo_state){
    if (slow_servo_millis + slow_servo_speed < millis()){
      motor_s.write(slow_servo_state);
      slow_servo_state++;      
      slow_servo_millis = millis();
    }  
  }
  if (slow_servo_state >= setted_slow_servo_state){
    if (slow_servo_millis + slow_servo_speed < millis()){
      motor_s.write(slow_servo_state);
      slow_servo_state--;      
      slow_servo_millis = millis();
    }  
  }
}


// change egg holder motor state by pressing button
void sbtn_motor_manual_control() {
  int sbtn_state = digitalRead(sbtn_pin);
  if (sbtn_state == 1){
    if (motor_current_state == 1){
      motor_current_state = 0;
      setted_slow_servo_state = motor_s_up_val;  
    } else {
      motor_current_state = 1;
      setted_slow_servo_state = motor_s_down_val;
    }
    
    slow_servo_millis = 0;
    motor_millis = millis();
    delay(500);
  }
}