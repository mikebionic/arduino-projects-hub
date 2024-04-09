#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


byte per[8] =
{
  0b00000,
  0b00010,
  0b00011,
  0b01110,
  0b11110,
  0b10010,
  0b11011,
  0b00000
};
byte arr[8] =
{
  0b00100,
  0b01010,
  0b11011,
  0b10001,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};

Ultrasonic ultrasonic(3,2);
//Ultrasonic ultrasonic(A0,A1);
int dog_in_thresh = 192;
int haski_recorded;
int haski_in_count = 0;
int current_sensor;
int s_nahar = 7;
int s_suw = 8;
Servo nahar_servo;
Servo suw_servo;
int suw_acyk = 180;
int suw_yapyk = 40;
int nahar_acyk = 80;
int nahar_yapyk = 10;

long feed_millis;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(1, per);
  lcd.createChar(2, arr);
  lcd.setBacklight(0x1);
  nahar_servo.attach(s_nahar);
  suw_servo.attach(s_suw);
  suw_servo.write(suw_yapyk);
  nahar_servo.write(nahar_yapyk);
  feed_millis = millis();

}

void loop(){
  lcd.clear();
  current_sensor = ultrasonic.Ranging(CM);
  Serial.println(current_sensor);
  if (current_sensor > dog_in_thresh){
    if (haski_recorded == 0){
      haski_in_count++;
    }
    lcd.print("Haski ichinde: ");
  } else {
    haski_recorded = 0;
    lcd.print("Haski dasynda: ");
  }
  lcd.setCursor (4,1);
  lcd.write (1);
  lcd.write (2);
  lcd.setCursor (7,1);
  lcd.print(haski_in_count);

  delay(1000);

  feed();
}



void feed(){
  if (feed_millis + 8000 < millis()){
    suw_servo.write(suw_acyk);
    nahar_servo.write(nahar_acyk);
    if (feed_millis + 10000 < millis()){
      suw_servo.write(suw_yapyk);
      nahar_servo.write(nahar_yapyk);
      feed_millis = millis();
    }
  }
}

