/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

#define WT_MIN        100
#define WT_MAX        450
#define MIC_PIN       2
#define WEIGHT_PIN    A5
#define SERVO_PIN     3
#define TRAVEL_ANGLE  90
#define ANGLE         TRAVEL_ANGLE / 2
#define OPEN_TIME     1500
#define WAIT_TIME     30000

Servo myservo;  // create servo object to control a servo

int weightMeasurement = 0;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  pinMode(WEIGHT_PIN, INPUT);
  pinMode(MIC_PIN, INPUT);
}

void loop() {
  if(digitalRead(MIC_PIN)) {
    weightMeasurement = analogRead(WEIGHT_PIN);
    if( (WT_MIN <= weightMeasurement) && (weightMeasurement <= WT_MAX) ) {
      cycleChuteDoor();
    }
    else delay(250);
    Serial.println(weightMeasurement);
  }
}

void cycleChuteDoor() {
  myservo.write(90-ANGLE);
  delay(OPEN_TIME / 2);
  myservo.write(90+ANGLE);
  delay(OPEN_TIME / 2 + WAIT_TIME);
}
