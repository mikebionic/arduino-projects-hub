// lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// rfid
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
int qtyOfCards = 2;
String registeredCards[] = {
  "D3:E8:C4:0A",
  "C9:EF:23:C2"
};

// servo
#include <Servo.h>
Servo door_servo;

// dht
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
// #define heater_relay 2
int temperature_thresh = 23;
DHT dht (DHTPIN, DHTTYPE);

// // keypad
// #include <Keypad.h>
// const byte ROWS = 4;
// const byte COLS = 4; 
// char keys[ROWS][COLS] = {
//   {'1','2','3'},
//   {'4','5','6'},
//   {'7','8','9'},
//   {'*','0','#'}
// };
// byte rowPins[ROWS] = {7, 6, 5, 4};
// byte colPins[COLS] = {3, 2, 1};
// char c[32];
// int i = 0;
// char pass[20] = {'1','2','3','4'};
// Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// rest
int door_buttonPin = 2;
int door_button_state = 0;
int door_gerkon = 3;
int door_gerkon_state = 0;
int door_servo_pin = 8;
int green_led_indicator = 4;
int red_led_indicator = 6;
int photoresistor_led_pin = 9;
int photoresistor_pin = 5;
int photoresistor_state = 0;
int buzzer = 7;
int gas_sensor_pin = A0;
int gas_sensor_value = 0;

// Bluetooth Serial
char serial_bt_stream;


void setup() {
  Serial.begin(9600);

  // rfid
  SPI.begin();
  rfid.PCD_Init();
  digitalWrite(red_led_indicator,1);
  digitalWrite(green_led_indicator,0);
  
  // lcd
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Salam!");
  delay(1000);
  lcd.clear();

  pinMode (door_buttonPin,INPUT_PULLUP);
  pinMode (green_led_indicator,OUTPUT);
  pinMode(photoresistor_led_pin,OUTPUT);
  pinMode(photoresistor_pin,INPUT);
  digitalWrite(green_led_indicator, 0);
  digitalWrite(red_led_indicator, 0);
  digitalWrite(photoresistor_led_pin, 0);

  door_servo.attach(door_servo_pin);
  
  dht.begin();
}


void loop() {
  btModule();
  buttonModule();
  rfidModule();
  photoresistorLedModule();
  gasModule();
  // keypadModule();
 
}

long dht_millis;
void temperatureModule(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (dht_millis + 2000 < millis()){
    Serial.print ("Temp = ");
    Serial.print (t);
    Serial.print (" *C ");

    Serial.print ("Humid = ");
    Serial.print (h);
    Serial.println (" % ");
    dht_millis = millis();
  }

  // if (t>temperature_thresh) {
  //   digitalWrite (heater_relay, HIGH);
  // } else if (t<temperature_thresh) {
  //   digitalWrite (heater_relay, LOW);
  // }
}


void btModule(){
  if (Serial.available() > 0) {
    serial_bt_stream = Serial.read();
    if(serial_bt_stream == '1'){
      openDoor();
    }
    if(serial_bt_stream == '2'){
      closeDoor();
    }
  }
}


void openDoor(){
  digitalWrite(green_led_indicator, 1);
  digitalWrite(red_led_indicator, 0);

  lcd.setCursor(2,0);
  lcd.print("Gapy acyldy!");
  lcd.setCursor(2,1);
  lcd.print("Hos geldiniz!");

  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  digitalWrite(green_led_indicator, 1);
  door_servo.write(170);
  delay(3000);

  lcd.clear();  
}

void closeDoor(){
  digitalWrite(green_led_indicator, 0);
  digitalWrite(red_led_indicator, 1);
  delay(400);
  door_servo.write(0);
}


void validateCard(String ID_key){
  for (int i = 0; i < qtyOfCards; i++){
    if (ID_key.indexOf(registeredCards[i]) >= 0){
      openDoor();
    }
  }
}


void buttonModule(){
  door_gerkon_state = digitalRead(door_gerkon);
  door_button_state = digitalRead(door_buttonPin);
  if (door_button_state == 1){
    openDoor();
  }
  if (door_gerkon_state == 1){
    closeDoor();
  }
}

void photoresistorLedModule(){
  photoresistor_state = digitalRead(photoresistor_pin);
  if (photoresistor_state == 1){
    digitalWrite(photoresistor_led_pin, 1);
  }
  else{
    digitalWrite(photoresistor_led_pin, 1);
  }
}


void gasModule(){
  gas_sensor_value = analogRead(gas_sensor_pin);
  if(gas_sensor_value > 400){
    tone(buzzer,450);
    delay(200);
    noTone(buzzer);
    delay(200);
  }else{
    noTone(buzzer);
  }
}

void rfidModule(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String ID_key = "";
  for (byte i = 0; i < 4; i++) {
    ID_key +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  ID_key.toUpperCase();

  // Serial.print("card_");
  // Serial.println(ID_key);
  validateCard(ID_key);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// void keypadModule(){
//   char key = keypad.getKey();
  
//   if(key){
//     if(key == '#'){delete_item();}
//     else if(i < 0){ i = 0;}
//     // else if(key == '#'){delete_all();}
//     else if(key == 'A'){
//       if(strcmp(c,pass) == 0){lcd.clear();lcd.print("Salam");lcd.setCursor(0,1);lcd.print("Hos Geldiniz");digitalWrite(9,1);s.write(85);delay(10000);digitalWrite(9,0);s.write(0);delete_all();}
//       else{lcd.clear();lcd.print("Gizlin soz");lcd.setCursor(0,1);lcd.print("Dogry dal");digitalWrite(8,1);delay(3000);digitalWrite(8,0);delete_all();}
//       }
//     else if(key == 'B'){
//         if(strcmp(c,pass) == 0){lcd.clear();lcd.print("Taze gizlin");lcd.setCursor(0,1);lcd.print("Soz");delay(2000);passChange();delete_all();}
//       }
//     else{
//     c[i++] = key;}
//     lcd.clear();
//     lcd.print(c);
//   }
// }

// void passChange(){
//   lcd.clear();
//   int index = 0;
//   passClear();
//   while(true){
//     char k = keypad.getKey();
//     if(k){
//       if(k == 'B' || k == 'C' || k == 'D'){continue;}
//       else if(k == '*'){break;}
//       lcd.print("*");
//       pass[index++] = k;s;
//     }
//   }
//   lcd.clear();
//   lcd.print("Gizlin soz"); 
//   lcd.setCursor(0,1);
//   lcd.print("tazelendi");
//   delay(1500);
// }


// void passClear(){
//   for(int t = 0; t<20;t++){
//     pass[t] = NULL;
//   }
// }

// void delete_item(){    
//   c[--i] = NULL;
// }

// void delete_all(){
//   for(int x = i; x>=0;x--){
//     c[x] = NULL;
//   }
//   i = 0;
// }

  
