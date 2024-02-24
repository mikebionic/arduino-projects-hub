const int stepPin = 3;
const int dirPin = 4;

int top_thresh = 12;
int position = 1;
int revolution_time = 3000;

int trigger = 7;
int trigger_state = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(trigger, INPUT_PULLUP);
}

void loop() {
  trigger_state = digitalRead(trigger);

  if (trigger_state == 1){
    down_state();
  }
  else {
    up_state();
  }
}

void down_state(){
  if (position > 1){
    go_down();
    position--;
  }
  else {
    halt_drive();
  }
}


void up_state(){
  if (position < top_thresh){
    go_up();
    position++;
  }
  else {
    halt_drive();
  }
}

void go_down(){
  digitalWrite(dirPin, 1);

  for(int x = 0; x<200; x++){
    digitalWrite(stepPin, 1);
    delayMicroseconds(revolution_time);
    digitalWrite(stepPin, 0);
    delayMicroseconds(revolution_time);
  }
//  delay (1000);
}

void go_up(){
  digitalWrite(dirPin, 0);

  for(int x=0; x<200; x++){
    digitalWrite(stepPin, 1);
    delayMicroseconds(revolution_time);
    digitalWrite(stepPin, 0);
    delayMicroseconds(revolution_time); 
  }
//  delay(1000);
}

void halt_drive() {
  digitalWrite(stepPin, 0);
}