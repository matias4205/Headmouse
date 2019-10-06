#include <Mouse.h>

int rightSensorPin  = A2;
int leftSensorPin = A3;    // IR Sensor

int lastLevelLeft = 0;
int lastLevelRight = 0;    // Previous IR level
int lastChangeLeft = 0;
int lastChangeRight = 0;  // Change in IR level
int changeThreshold = 5; // How hard a rising edge do we need?
 
//visualization
int primaryClickDuration = 250;        // Length of visualization
int secondaryClickDuration = 500;
float lastStartRight = 0;       // Last start of visualization
float lastStartLeft = 0;

void setup() {
  Serial.begin(9600);      // Debug constructor
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}

void loop() {
  int rightSensorValue = analogRead(rightSensorPin); //1020
  int leftSensorValue = analogRead(leftSensorPin); //1020
  
  if(Serial.available()){
    Mouse.click(MOUSE_LEFT);
  }

  printValues(leftSensorValue, rightSensorValue);
  
  // look for rising edges
  lastChangeLeft = leftSensorValue - lastLevelLeft; //1020
  lastLevelLeft = leftSensorValue; //1020

  lastChangeRight = rightSensorValue - lastLevelRight;
  lastLevelRight = rightSensorValue;

  evaluateClick();
  
  delay(100);
}

void printValues(int _leftSensorValue, int _rightSensorValue){
  Serial.print("Left");
  Serial.println(_leftSensorValue);  // Read Data
  Serial.print("Right");
  Serial.println(_rightSensorValue);  // Read Data  
}

void evaluateClick(){
  int _currentMillis = millis();
  
  if (lastChangeRight >=changeThreshold) {
    Serial.print("TUVE UN CAMBIO! ");
    Serial.println(lastChangeRight);

    if (_currentMillis >= (lastStartRight + secondaryClickDuration)) {
      Serial.println(" -> SECUNDARIOOOOOOOOOOOOOOOOO");
    } else if (_currentMillis >= (lastStartRight + primaryClickDuration)) {
      Serial.println("PRIMAAAAAAAAARIOOOOOOOOOOO");
    }

    lastStartRight = _currentMillis;
  }

  if (lastChangeLeft >=changeThreshold) {
    lastStartLeft = _currentMillis;
    Mouse.click(MOUSE_LEFT);
  }
  if (_currentMillis >= lastStartLeft + primaryClickDuration) {
  }  
}