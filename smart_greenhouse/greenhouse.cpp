#include <dht.h>
#include <LiquidCrystal_I2C.h> 
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;
#define DHT11_PIN 12
int fan = 10;
int cyra = 13;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
	pinMode(fan, OUTPUT);
	pinMode(cyra, OUTPUT);
}

void loop()
{
	
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Cyglyk ");
	Serial.print(DHT.humidity);
  Serial.print(",\t");
	Serial.print(" Temp ");
  Serial.println(DHT.temperature);
  lcd.setCursor (0,0);
	lcd.print("Cyglyk ");
	lcd.setCursor (7,0);
	lcd.print(DHT.humidity);
	lcd.setCursor (1,1);
	lcd.print(" Temp ");
  lcd.setCursor (7,1);
	lcd.println(DHT.temperature);
	if (DHT.temperature > 23){
		digitalWrite(fan, 1);
		digitalWrite(cyra, 0);
	} else {
		digitalWrite(fan,0);
		digitalWrite(cyra, 1);
	}
  delay(2000);
}

