#include <Time.h>
#include <TimeLib.h>

#include <VirtualWire.h>
#include <EasyTransferVirtualWire.h>
 int p1=A1;
 int p2=A2; 
 int p3=A3;
 int p4=A4;
 int p5=A5;
/*const int p3=A2;
const int p4=A3;
const int p5=A4;
*/
EasyTransferVirtualWire ET;
struct SEND_DATA_STRUCTURE{
  //byte ID;
int p1;
 int p2; 
 int p3; 
 int p4; 
 int p5; 
/*const int p3;
const int p4;
const int p5;
*/

};
SEND_DATA_STRUCTURE mydata;

void setup() {
  ET.begin (details(mydata));
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_tx_pin(8);
   randomSeed(analogRead(0));
    //mySwitch.enableTransmit(10);
   // mydata.ID=1; 
 
}
void loop() {
//    sensor.read(p1);
   mydata.p1=analogRead(p1);
   mydata.p2=analogRead(p2);
   mydata.p3=analogRead(p3);
   mydata.p4=analogRead(p4);
   mydata.p5=analogRead(p5);
   // mydata.humid= sensor.humid;
    ET.sendData();
   // delay (1000); //random(5000,1000);
  }
