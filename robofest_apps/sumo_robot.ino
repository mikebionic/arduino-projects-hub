#define sag_1 3
#define sag_2 4
#define cep_1 5
#define cep_2 6
#define enA 2
#define enB 7


#define kowsh_1 8
#define kowsh_2 9

#include <Servo.h>
Servo myservo;
Servo tormoz;
char stream = 0;
int sag_1_state = 0;
int sag_2_state = 0;
int cep_1_state = 0;
int cep_2_state = 0;


void setup() {
  Serial.begin(9600);
  pinMode (sag_1, OUTPUT);
  pinMode (sag_2, OUTPUT);
  pinMode (cep_1, OUTPUT);
  pinMode (cep_2, OUTPUT);
  pinMode (enA, OUTPUT);
  pinMode (enB, OUTPUT);
  pinMode (kowsh_1, OUTPUT);
  pinMode (kowsh_2, OUTPUT);
  digitalWrite(enA, 1);
  digitalWrite(enB, 1);

//  myservo.attach(8);//servo kod
//  tormoz.attach(9);//servo kod
  
//  tormoz.write(70);
//  myservo.write(110);
}

void loop() {
  
//        digitalWrite(kowsh_1, 1);
//        digitalWrite(kowsh_2, 0);
        delay(200);
  if (Serial.available() > 0) {
//    stream = btModule.read();
    Serial.println(stream);
    stream = Serial.read();
//      Serial.print(data); 
//    stream.trim();    
//    if (stream.length() > 0) {
      if(stream == '1'){
//       Serial.println("one yoreyaris");
         one_yore();
           }
      if (stream == '2'){
//        Serial.println("yza yoreyaris");
          yza_yore();
      }
      if (stream == '4'){
        
        Serial.println("saga yoreyaris");
          saga_owrum();
      }
      if (stream == '3'){
         Serial.println("cepe yoreyaris");
          cepe_owrum();
      }
      if (stream == '0'){
          stop();
      }
      if(stream =='8'){
        Serial.println ("servo acylyar");
        digitalWrite(kowsh_1, 0);
        digitalWrite(kowsh_2, 1);
//        delay(200);
//        digitalWrite(kowsh_1, 0);
//        digitalWrite(kowsh_2, 0);
        
        ////  acyldy();
        //myservo.write(0);
        //
        ////acyldy();
        //tormoz.write(180);
      }

      
      if (stream == '5'){
        digitalWrite(kowsh_1, 0);
        digitalWrite(kowsh_2, 0);
      }
      
       if (stream =='9'){
        digitalWrite(kowsh_1, 1);
        digitalWrite(kowsh_2, 0);
//        delay(200);
//        digitalWrite(kowsh_1, 0);
//        digitalWrite(kowsh_2, 0);
//        Serial.println ("servo yapylyar");
        ////yapyldy();
        //myservo.write(110);
        //
        ////yapyldy();
        //tormoz.write(70);
       }
     }
 
  digitalWrite(sag_1, sag_1_state);
  digitalWrite(sag_2, sag_2_state);
  digitalWrite(cep_1, cep_1_state);
  digitalWrite(cep_2, cep_2_state);
}



void one_yore(){
 sag_1_state = 1;
 sag_2_state = 0;
 cep_1_state = 0;
 cep_2_state = 1;
 
  
}

void yza_yore(){
  sag_1_state =0;
 sag_2_state = 1;
 cep_1_state = 1;
 cep_2_state = 0;
 
}


void cepe_owrum(){
 sag_1_state = 0;
 sag_2_state = 1;
 cep_1_state = 0;
 cep_2_state = 1;
}


void saga_owrum(){
 sag_1_state = 1;
 sag_2_state = 0;
 cep_1_state = 1;
 cep_2_state = 0;
}


void stop(){ 
 sag_1_state = 0;
 sag_2_state = 0;
 cep_1_state = 0;
 cep_2_state = 0;
}
//SUMO ROBOT KODY !!!!


