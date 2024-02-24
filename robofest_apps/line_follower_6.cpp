
int left_most_Sensor = A4;
int leftSensor = A3;
int left_close_Sensor = 9;
int midSensor = A2;
int right_close_Sensor = 8;
int rightSensor = A1;
int right_most_Sensor = A0;

char data[100];
String sensorsData = "0000000";
String thisTurn = "forward";

int super_slowSpeed = 60;
int slowSpeed = 100;
int midSpeed = 150;
int maxSpeed = 230;

// Motors
#define sag1 2
#define sag2 3
#define cep1 4
#define cep2 7
#define right_en 5
#define left_en 6

int sag1_state = 0;
int sag2_state = 0;
int cep1_state = 0;
int cep2_state = 0;
// Motors

void setup() {
    Serial.begin(9600);
    pinMode(sag1, OUTPUT);
    pinMode(sag2, OUTPUT);
    pinMode(cep1, OUTPUT);
    pinMode(cep2, OUTPUT);
    pinMode(right_en, OUTPUT);
    pinMode(left_en, OUTPUT);

    pinMode(left_most_Sensor, INPUT);
    pinMode(leftSensor, INPUT);
    pinMode(left_close_Sensor, INPUT);
    pinMode(midSensor, INPUT);
    pinMode(right_close_Sensor, INPUT);
    pinMode(rightSensor, INPUT);
    pinMode(right_most_Sensor, INPUT);

//    analogWrite(right_en, slowSpeed);
//    analogWrite(left_en, slowSpeed);
}


void loop(){
  updateColorValues();
  calculate_and_run2();
  //forward();

  digitalWrite(sag1,sag1_state);
  digitalWrite(sag2,sag2_state);
  digitalWrite(cep1,cep1_state);
  digitalWrite(cep2,cep2_state);
}

void updateColorValues(){
    
    sprintf(data, "%d%d%d%d%d%d%d",
        !digitalRead(left_most_Sensor),
        !digitalRead(leftSensor),
        digitalRead(left_close_Sensor),
        !digitalRead(midSensor),
        digitalRead(right_close_Sensor),
        !digitalRead(rightSensor),
        !digitalRead(right_most_Sensor)
    );
    sensorsData = String(data);

    Serial.print("Turn: __ ");
    Serial.print(thisTurn);

    Serial.print("     ");
    Serial.print(sensorsData == "0010000");

    Serial.print("    __  DATA:  ");
    Serial.println(sensorsData);
}

// 0 0 0 0 1
// right()

// 0 0 0 1 1
// right_slow()

// 0 0 0 1 0
// right_slow() + mid_speed_left

// 0 0 1 0 0
// forward()

// 0 1 0 0 0
// left_slow() + mid_speed_right

// 1 1 0 0 0
// left_slow()

// 1 0 0 0 0
// left()
void calculate_and_run2(){
    
  if (sensorsData == "0010000" || sensorsData == "0001000" || sensorsData == "0000100"){
    forward();
    if (sensorsData == "0010000"){
        thisTurn = "forward_right";
        analogWrite(right_en, midSpeed);
        analogWrite(left_en, super_slowSpeed);
    }    
    if (sensorsData == "0000100"){
        thisTurn = "forward_left";
        analogWrite(right_en, super_slowSpeed);
        analogWrite(left_en, midSpeed);
    }
    else {
        thisTurn = "forward";
        analogWrite(right_en, midSpeed);
        analogWrite(left_en, midSpeed);
    }
  }

  if(sensorsData == "0100000"){
    thisTurn = "left_slow";
    left_slow();
    analogWrite(right_en, slowSpeed);
    analogWrite(left_en, slowSpeed);
  }

  if(sensorsData == "0000010"){
    thisTurn = "right_slow";
    right_slow();
    analogWrite(right_en, slowSpeed);
    analogWrite(left_en, slowSpeed);
  }

  if(sensorsData == "1000000"){
    thisTurn = "left";
    left();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }

  if(sensorsData == "0000001"){
    thisTurn = "right";
    right();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }

  if(sensorsData == "1100000"){
    thisTurn = "left";
    left();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "0000011"){
    thisTurn = "right";
    right();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }

  if(sensorsData == "0110000"){
    thisTurn = "left";
    left();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "0000110"){
    thisTurn = "right";
    right();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }

  
  if(sensorsData == "0011000"){
    thisTurn = "left_slow";
    left_slow();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "0001100"){
    thisTurn = "right_slow";
    right_slow();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  
  if(sensorsData == "0011100"){
    thisTurn = "forward";
    forward();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "0001110"){
    thisTurn = "right_slow";
    right_slow();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "0111000"){
    thisTurn = "left_slow";
    left_slow();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  
  if(sensorsData == "0000111"){
    thisTurn = "right";
    right();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }
  if(sensorsData == "1110000"){
    thisTurn = "left";
    left();
    analogWrite(right_en, midSpeed);
    analogWrite(left_en, midSpeed);
  }

   
  if(sensorsData == "0001111"){
    thisTurn = "right";
    right();
    analogWrite(right_en, maxSpeed);
    analogWrite(left_en, maxSpeed);
  }
  if(sensorsData == "1111000"){
    thisTurn = "left";
    left();
    analogWrite(right_en, maxSpeed);
    analogWrite(left_en, maxSpeed);
  }

}


void forward(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 1;
    cep2_state = 0;
}

void right(){
    sag1_state = 1;
    sag2_state = 0;
    cep1_state = 1;
    cep2_state = 0;
}

void left(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 0;
    cep2_state = 1;
}
void right_slow(){
    sag1_state = 0;
    sag2_state = 0;
    cep1_state = 1;
    cep2_state = 0;
}

void left_slow(){
    sag1_state = 0;
    sag2_state = 1;
    cep1_state = 0;
    cep2_state = 0;
}