#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

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
byte arr[8] = 
{
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00000,
  0b00000
};



Ultrasonic ultrasonic(A0,A1);
 int Height;

void setup() {
  
pinMode (17,OUTPUT);
pinMode (16,OUTPUT);
 digitalWrite (17,HIGH);
 digitalWrite (16,HIGH);

 
    lcd.begin(16, 2);
    lcd.createChar(1, per);
    lcd.createChar(2, arr);
    lcd.setBacklight(0x1);
     }

void loop()
{
  lcd.clear();
  //lcd.print("Distance: ");
  //lcd.print(ultrasonic.Ranging(CM));
  //lcd.print("cm");
  //lcd.setCursor(0, 1);
  lcd.print("Sizin boyunyz: ");
  lcd.setCursor (4,1);
lcd.write (1);
lcd.write (2);

lcd.setCursor (7,1);
  Height=200-(ultrasonic.Ranging(CM));
  lcd.print(Height);
  lcd.print("cm");

    
  delay(1000);
  }




