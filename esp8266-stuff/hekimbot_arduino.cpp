#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);

int photoresistor_pin = A0;
int piezo = A1;

int red_pin = 9;
int green_pin = 10;
int blue_pin = 11;

int photo_state = 0;
long x;

byte per[8] = 
{
  0b00100,
  0b00000,
  0b01110,
  0b10101,
  0b00100,
  0b01010,
  0b10001,
  0b00000
};

Ultrasonic ultrasonic(A2,A3);

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.createChar(1, per);

  pinMode(photoresistor_pin, INPUT);
  // pinMode(piezo, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

}


void loop(){
  display();
  sound();
  photoresistor();
}


void display(){
  lcd.clear();
  lcd.print("Sizin boyunyz: ");
  lcd.setCursor (4,1);
  lcd.write (1);
}

void photoresistor(){
  photo_state = analogRead(photoresistor_pin);
  Serial.print("Photo: ");
  Serial.println(photo_state);
}

void sound() {
  if (x+400 < millis()){
    tone(piezo, 500);
    if (x+800 < millis()){
      noTone(piezo);
      x = millis();
    }
  }
}
