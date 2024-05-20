
int left_btn = 2;
int right_btn = 3;
int left_motor = 5;
int right_motor = 10;
int left_btn_state = 0;
int right_btn_state = 0;

int rotation_current_state = 3;
long rot_millis = millis();
int button_pressed = 0;
int delay_time = 3000;
int floating_delay_time = 2000;
long some_floating_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_btn, INPUT);
  pinMode(right_btn, INPUT);  
  pinMode(left_motor, OUTPUT);
  pinMode(right_motor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  left_btn_state = digitalRead(left_btn);
  right_btn_state = digitalRead(right_btn);

  
  Serial.print("      ");
  Serial.print(rot_millis);
  Serial.print("      ");
  Serial.print(left_btn_state);
  Serial.print("      ");
  Serial.println(right_btn_state);
    

  Serial.println(rotation_current_state);

  if (button_pressed == 0){
    rot_millis = millis();
  }
  
  if (some_floating_time + floating_delay_time < millis()){
    if (left_btn_state == 1){
      rotation_current_state = 2;
      button_pressed = 1;  
    }    
  }
  
  if (some_floating_time + floating_delay_time < millis()){
    if (right_btn_state == 1){
      rotation_current_state = 1;
      button_pressed = 1;
    }
  }


  if (rotation_current_state == 1){
    Serial.println("state is 1");
    if (rot_millis + delay_time < millis()){
      Serial.println("Motor running left");
      digitalWrite(left_motor,1);
      digitalWrite(right_motor,0);
      button_pressed = 0;
    } else {
      some_floating_time = millis();
      Serial.println("___________ motor off");
      digitalWrite(left_motor,0);
      digitalWrite(right_motor,0);
    }
  }
  else if (rotation_current_state == 2){
    Serial.println("state is 2");
    if (rot_millis + delay_time < millis()){
      Serial.println("Motor running right");
      digitalWrite(left_motor,0);
      digitalWrite(right_motor,1);
      button_pressed = 0;
    } else {
      some_floating_time = millis();
      Serial.println("___________ motor off");
      digitalWrite(left_motor,0);
      digitalWrite(right_motor,0);
    }
  }

  if (rotation_current_state == 0){
    Serial.println("___________ motor off");
    digitalWrite(left_motor,0);
    digitalWrite(right_motor,0);
  }

  if (rotation_current_state == 3){
    Serial.println("              state is 3, just running");
    digitalWrite(left_motor,1);
    digitalWrite(right_motor,0);
  }


}
