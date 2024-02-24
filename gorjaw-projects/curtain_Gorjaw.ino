#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h> 

#define ServoPin 14
Servo myservo;
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn" target="myIframe">LED ON</a><br>
Ciclk to turn <a href="ledOff" target="myIframe">LED OFF</a><br>
LED State:<iframe name="myIframe" width="100" height="25" frameBorder="0"><br>
<hr>
<a href="https://circuits4you.com">circuits4you.com</a>
</center>

</body>
</html>
)=====";


#define LED1 0
#define LED2 1
#define bt1 2 
#define bt2 3 




IPAddress staticIP(192, 168, 1, 210); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
const char* deviceName = "Smart lights v2";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "curtain_hash";


ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handle0on() { 
 Serial.println("LED on page");
 digitalWrite(LED1,LOW); //LED is connected in reverse
 digitalWrite(LED2,HIGH);
 delay(30000);
  digitalWrite(LED1,LOW); //LED is connected in reverse
 digitalWrite(LED2,LOW);
 server.send(200, "text/html", "one"); //Send ADC value only to client ajax request
 if(digitalRead(bt1 == 1)){
   digitalWrite(LED1,LOW); 
   digitalWrite(LED2,LOW);
  }
}
void handle0off() { 
 Serial.println("LED off page");
 digitalWrite(LED1,HIGH); //LED off
 digitalWrite(LED2,LOW);
 delay(30000);
 digitalWrite(LED1,LOW); //LED is connected in reverse
 digitalWrite(LED2,LOW);
 server.send(200, "text/html", "yza"); //Send ADC value only to client ajax request
 if(digitalRead(bt2 == 1)){
   digitalWrite(LED1,LOW); 
   digitalWrite(LED2,LOW);
  }
}


//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED1,OUTPUT); 
   pinMode(LED2,OUTPUT);
    pinMode(bt1,INPUT);
    pinMode(bt2,INPUT);
    digitalWrite(LED1,LOW); 
    digitalWrite(LED2,LOW); 
   
   

    

  
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
   server.on("/led0on", handle0on); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/led0off", handle0off);
  
  

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient(); 
  
}
