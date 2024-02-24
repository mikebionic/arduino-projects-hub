#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

//Static IP address configuration
IPAddress staticIP(192, 168, 43, 223); //ESP static ip
IPAddress gateway(192, 168, 43, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ino";
const char* password = "blablabla";
const char* deviceName = "hekim";
String serverUrl = "192.168.43.252";
String payload;
String device_key = "111";
String command = "water_measurer_sensor";

ESP8266WebServer server(80);

String stream;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
 
//  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
//  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
 
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
  sendDataFromMaster();
}


void sendDataFromMaster(){
  stream="";
  if (Serial.available() != 0){
    stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0){
      String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(stream);
			String arg_data = "?doctor_id=3&state="+stream; 
      Serial.println(arg_data);
      sendRequest("http://"+serverUrl+"/update_latest/",argument_data);
    }
  }
}


void sendRequest(String path, String sendingData){
  if(WiFi.status()== WL_CONNECTED){
    String serverPath = path+sendingData;
    Serial.println(serverPath);
    payload = httpGETRequest(serverPath.c_str());
    Serial.println(payload);
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}


String httpGETRequest(const char* serverName) {
  HTTPClient http;
  http.begin(serverName);
  int httpResponseCode = http.GET();  
  String payload = "{}"; 
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}

void handleDevice() {
  String name = server.arg("name");
  String title = server.arg("title");
  name.trim();
  title.trim();
	Serial.println(name + ":" + title + ":");
  server.send(200, "text/html", "OK");
}