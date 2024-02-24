#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

int button = 2;
int led = 13;  //13
int relay = 9;
int erase_button = 3;

FPS_GT511C3 fps(6, 7); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)

  void setup()
  {
    pinMode(relay,OUTPUT);
    pinMode(led,OUTPUT);
    pinMode(button,INPUT_PULLUP);
    pinMode(erase_button,INPUT_PULLUP);
    digitalWrite(led,0);
    digitalWrite(relay,0);
        
    Serial.begin(9600); //set up Arduino's hardware serial UART
    delay(100);
    fps.Open();
  }

char query = '*';


///////////////////////////////////////////////////
  void loop()
  {
    long sec = millis();
    
    //blink();
    query = '*';
    if(Serial.available()>0){
     query = Serial.read();}
    while (digitalRead(button)==0){
      openDoor();
      if ((sec+5000)<millis()){
        query = '1';
        break; 
      }
    }
    while (digitalRead(erase_button)==0){
      query = 'D';
      break;
    }
    
   switch(query){
    case '1':  Enroll();break;
    case 'D':  fps.DeleteAll();break;
    default:  getid(); break;    
   }
    delay(50);     
    query = '*';
  }

    
void openDoor(){
  digitalWrite(relay,1);
  delay(1000);
  Serial.println("door open");
  digitalWrite(relay,0);
}

void blink(){
  fps.SetLED(true);
  delay(1000);
  fps.SetLED(false);
  delay(1000);
}



//////////////////////////////////////////////////////////////////////////
void Enroll()
{
 digitalWrite(led,1);
    fps.SetLED(true);
   int enrollid = 0;
  bool usedid = true;
  while (usedid == true)
  {
    usedid = fps.CheckEnrolled(enrollid);
    if (usedid==true) enrollid++;
  }
  fps.EnrollStart(enrollid);

  // enroll
  Serial.print("Press finger to Enroll #");
  Serial.println(enrollid);
  while(fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  if (bret != false)
  {
    Serial.println("Remove finger");
    fps.Enroll1(); 
    while(fps.IsPressFinger() == true) delay(100);
    Serial.println("Press same finger again");
    while(fps.IsPressFinger() == false) delay(100);
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      Serial.println("Remove finger");
      fps.Enroll2();
      while(fps.IsPressFinger() == true) delay(100);
      Serial.println("Press same finger yet again");
      while(fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        Serial.println("Remove finger");
        iret = fps.Enroll3();
        if(iret == 0)
        {
   //       inf = '1';
          Serial.println("Enrolling Successful");
     
        }
      
        else
        {
          Serial.print("Enrolling Failed with error code:");
          Serial.println(iret);
        }
      }
      else Serial.println("Failed to capture third finger");
    }
    else Serial.println("Failed to capture second finger");
  }
  else Serial.println("Failed to capture first finger");
  digitalWrite(led,0);
}
      

/////////////////////////////////////////////////////////////////////////////////////////////  
void getid()
{
  fps.SetLED(true);
  //int a=0;

 //while (a=1){
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
   int id = fps.Identify1_N();
    if (id <200)
    {
      Serial.print("Verified ID:");
      Serial.println(id);
      openDoor();
    }
    else
    {
      Serial.println("Finger not found");
    }
  }
  else
  {
    Serial.println("Please press finger");

// a=1;    //for some loops in voids
fps.SetLED(false);
}
  delay(200);
 
 }

///////////////////////////////////////////////////////////////////////////////////////////



