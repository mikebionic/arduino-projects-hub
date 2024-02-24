
int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";



// Socketlerin pineri
int sock1pin = 22; // D0
int sock2pin = 23; // D1
int sock3pin = 24; // D2

// aircondinsionerin pinleri
int condmodelow = 25; 
int condmodemed = 26;
int condmodehigh = 27;

// PIR sensor
int pirsensorpin = 4;
int pirsensorled = 28;

// take this from devices_config of specific device
String socket_command = "socket";
/////

// device config-dan almaly bu value
String pir_device_command = "sensor_state";

void setup() {
  Serial.begin(115200);
  pinMode(led,OUTPUT);

  //socketlerin pinleri
  pinMode(sock1pin, OUTPUT);
  pinMode(sock2pin, OUTPUT);
  pinMode(sock3pin, OUTPUT);
  ////
  
  //aircondinsionerin pinleri
  pinMode(condmodelow, OUTPUT);
  pinMode(condmodemed, OUTPUT);
  pinMode(condmodehigh, OUTPUT);
  ////
  
  //pir sensor
  pinMode(pirsensorpin, INPUT);
  pinMode(pirsensorled, OUTPUT);
}


void send_uart_message(String command, String action){
  String payload = "command="+command+"&action="+action;
  Serial.println(payload);
}


void loop() {
  if(Serial.available() != 0){
    String stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      command = getStringPartByDelimeter(stream,':',0);
      action = getStringPartByDelimeter(stream,':',1);
      process_key = getStringPartByDelimeter(stream,':',2);

      if (process_key == arduino_process_key){
        control_device(command, action);
      }

    }
  }
  //pir sensor
  int pirsensorstate = digitalRead(pirsensorpin);
  if(pirsensorstate == 1) {
  send_uart_message(pir_device_command, "1");
  digitalWrite(pirsensorled, 1);
}
  else if(pirsensorstate == 0) {
  	//ochende ibermesen gowy bolar
  // send_uart_message(pir_device_command, "0");
  digitalWrite(pirsensorled, 0);
}
}


String getStringPartByDelimeter(String data, char separator, int index){
  int stringData = 0;
  String dataPart = "";
  for(int i = 0; i<data.length()-1; i++){
    if(data[i]==separator) {
      stringData++;
    }else if(stringData==index) {
      dataPart.concat(data[i]);
    }else if(stringData>index){
      return dataPart;
      break;
    }
  }
  return dataPart;
}


void control_device(String command, String action){

  // socket control functions
  if (command == "socket1") {
    if(action == "1"){
        digitalWrite(sock1pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock1pin,0);
    }
  }
  else if (command == "socket2"){
    if(action == "1"){
        digitalWrite(sock2pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock2pin,0);
    }
  }
  else if (command == "socket3"){
    if(action == "1"){
        digitalWrite(sock3pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock3pin,0);
    }

    else if (action == "uartoff"){
      send_uart_message("0", socket_command);
    }
  }
  //////
  
  
// condinsioner control functions
//mode_high
  if (command == "mode_low") {
    if(action == "1"){
        digitalWrite(condmodelow,1);
    }
    else if(action == "0"){
        digitalWrite(condmodelow,0);
    }
  }
  
//mode_med
if (command == "mode_med") {
    if(action == "1"){
        digitalWrite(condmodemed,1);
    }
    else if(action == "0"){
        digitalWrite(condmodemed,0);
    }
  }
  
//mode_high
if (command == "mode_high") {
    if(action == "1"){
        digitalWrite(condmodehigh,1);
    }
    else if(action == "0"){
        digitalWrite(condmodehigh,0);
    }
  }


  if (command == "led13"){
    if (action == "on"){
      digitalWrite(led, 1);
    }
    else if (action == "off"){
      digitalWrite(led, 0);
    }
  }
}
