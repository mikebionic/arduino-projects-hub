#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 10
#define RST_PIN 9

int button_state = 0;
int buttonPin = 7;
int ledIndicator = 2;
int resetPin = 5;

int btn_state_pin = 3;
int wifi_serial_pin = 4;
int rfid_validation_pin = 6;


int doorDelay = 500;
long reset_timeout = 2400000;


MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int qtyOfCards = 15;
String registeredCards[] = {
  "46:0C:C8:0F", //gulbahar
  "26:B8:3C:1E", //mike
  "A6:88:E8:21", //selbi ilmyradova
  "23:BB:97:79", //dowletyar
  "C6:1D:D6:21", //Merdan
  "06:75:BC:1E", //dowlpack
  "86:FA:DF:21", //mati
  "6A:2B:5C:9C", //mekan
  "66:E5:D6:21", //dayanch
  "8A:4B:81:7F", //keychain (line)
  "C9:CE:B1:C2", //keychain
  "56:9B:CC:0F", // merdan (green cutted)
  "A6:5C:37:11", // merdan (blue bus card)
  "80:86:80:74", // Gelneje (cleaner)
  "96:D2:CB:0F", // Bagtyyar, berkarar LANY

};


void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode (buttonPin,INPUT_PULLUP);
  pinMode (ledIndicator,OUTPUT);
  digitalWrite(resetPin,1);
  pinMode (resetPin, OUTPUT);
  digitalWrite(ledIndicator, 0);

  pinMode (btn_state_pin, OUTPUT);
  digitalWrite(btn_state_pin, 0);
  pinMode (wifi_serial_pin, OUTPUT);
  digitalWrite(wifi_serial_pin, 0);
  pinMode (rfid_validation_pin, OUTPUT);
  digitalWrite(rfid_validation_pin, 0);
}


void loop() {
  buttonModule();
  rfidModule();
  wifiSerialModule();
  autoResetTimeout();
}


void openDoor(){
  digitalWrite(ledIndicator, 1);
  delay(doorDelay);
  digitalWrite(ledIndicator, 0);
  delay(500); // for electrical security
}


void validateCard(String ID_key){
  for (int i = 0; i < qtyOfCards; i++){
    if (ID_key.indexOf(registeredCards[i]) >= 0){
      
    Serial.println("card validated " + millis());
  digitalWrite(rfid_validation_pin, 1);
      openDoor();
      Serial.println(registeredCards[i]);
    }
  }
}


void buttonModule(){
  button_state = digitalRead(buttonPin);
  if (button_state == 0){
    Serial.println("button clicked " + millis());
    
    digitalWrite(btn_state_pin, 1);
    openDoor();
  }
}


void rfidModule(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println(F("Your tag is not of type MIFARE Classic."));
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

//  Serial.print("Card key: ");
  Serial.println(ID_key);

  validateCard(ID_key);

  delay(1000);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void wifiSerialModule(){
  String stream="";
  if (Serial.available()!=0){
    stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      if (stream == "open_door"){
  digitalWrite(wifi_serial_pin, 1);
        openDoor();
      }
    }
  }
}


void(* resetFunc) (void) = 0;

void autoResetTimeout(){
  if (millis() >= reset_timeout){
    digitalWrite(resetPin, 0);
    Serial.println("reset called " + millis());
    resetFunc();
  }
}
