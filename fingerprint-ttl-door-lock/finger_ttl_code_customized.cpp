#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

FPS_GT511C3 fps(4, 5); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)

void setup()
{
  Serial.begin(9600); //set up Arduino's hardware serial UART
  delay(100);
  fps.Open();
//while (true){  
 //blink();
  //}
/*if (fps.FPS_GT511C3){
  delay(1000);
}
else{

 while (true){
blink();
 }
} 
*/
   
}
char query = '*';
//char inf = '0';

//////////////////////////////////////////////////////////////////////////
void Enroll()
{
  //boolean c=false;
 //inf = '0';
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
/*
  switch (inf){
  case '1' :  break;   //got how to make it but it's not required shit))))))))
}
*/
}
      
uint8_t kid;
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
      kid=id;
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

void loop()
{
  //blink();
  query = '*';
  if(Serial.available()>0){
   query = Serial.read();}
   
 switch(query){
  case '1':  Enroll();break;
  default:  getid();break;    
 }
  delay(50);     
  query = '*';
 // uint8_t= k
    Serial.print(kid);
    if (kid=3){
      Serial.print("Muhammed");
    }
}


void blink(){
  fps.SetLED(true);
  delay(1000);
  fps.SetLED(false);
  delay(1000);
}


