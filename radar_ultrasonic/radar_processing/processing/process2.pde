import processing.serial.*;

int max_distance = 40;
float coefCmPx;

Serial arduinoPort;
String data;   

int w = 1620;
int h = 820;
int index;         
float angle    = 0; 
float distance = 0; 
float distancePx = 0;

void setup() {
  size(1620, 820);
  background(20, 0, 0);
  String portName    = Serial.list()[0];
  arduinoPort        = new Serial(this, portName, 9600);
  arduinoPort.bufferUntil('\n');
  
  coefCmPx = h / max_distance;
  
  smooth();
}


void drawRadar() {
  pushMatrix();
  translate(w/2, h);
  noFill();
  strokeWeight(1);
  stroke(98, 245, 31);
  arc(0, 0, 2*h-40, 2*h-40, PI, TWO_PI);
  arc(0, 0, 3*h/2-15, 3*h/2-15, PI, TWO_PI);
  arc(0, 0, h-15, h-15, PI, TWO_PI);
  arc(0, 0, h/2-15, h/2-15, PI, TWO_PI);
  
  line(0, 0, -w*cos(radians(30)), -w*sin(radians(30)));
  line(0, 0, -w*cos(radians(60)), -w*sin(radians(60)));
  line(0, 0, -w*cos(radians(90)), -w*sin(radians(90)));
  line(0, 0, -w*cos(radians(120)), -w*sin(radians(120)));
  line(0, 0, -w*cos(radians(150)), -w*sin(radians(150)));
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(2);
  stroke(30, 250, 60);
  translate(w/2, h);
  line(0, 0, (w/2-10)*cos(radians(angle)), -(w/2-10)*sin(radians(angle)));
  popMatrix();
}

// Draw obstacles
void drawLineObstacle() {
  pushMatrix();
  translate(w/2, h);
  strokeWeight(2);
  stroke(255,10,10);

  if(distance < max_distance && distance != 0) {
    distancePx = coefCmPx * distance;
    line(distancePx*cos(radians(angle)),
          -distancePx*sin(radians(angle)),
          (w/2-10)*cos(radians(angle)),
          -(w/2-10)*sin(radians(angle)));
  }
  popMatrix();
}

void draw() {
  noStroke();
  fill(30, 5); 
  rect(0, 0, w, h);
  
  drawRadar();
  drawLine();
  drawLineObstacle();
  dataDraw();
  text("90", w/2, h/12);
  text("0", (w - w/12), h-10);
  text("180", (w/12), h-10);
  //text("90", w/2, h/4);
}


void dataDraw(){  
  textSize(18);
  fill(255, 204, 0);
  text("Nyshan uzaklyk:   " + distance + " sm", 10, 60);
  text("Gradus:                    " + angle + "*", 10, 30);
}

void serialEvent (Serial myPort) {
  data = myPort.readStringUntil('\n');
  if(data != null) {
    index    = data.indexOf(",");
    angle    = float(data.substring(0, index));
    distance = float(data.substring(index+1, data.length()-1));
  }
  println(distance);
}
