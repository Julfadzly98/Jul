// EasyBot Program

#include <Servo.h>

#define dirA 2    // L9110S A-1A
#define speedA 3  // L9110S A-1B
#define dirB 4    // L9110S B-1A
#define speedB 5  // L9110S B-1B
#define servo 6
#define echo 7
#define trig 8
#define buzzer 9
#define sensorL 10
#define sensorC 11
#define sensorR 12
#define STATUS 13

int MTSPEED = 50; // Motor Speed

int distance;

Servo head;

void setup() {
  // Setup HC-SR04 sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Setup line tracking sensor
  pinMode(sensorL, INPUT);
  pinMode(sensorC, INPUT);
  pinMode(sensorR, INPUT);

  // Setup motor driver module
  pinMode(dirA, OUTPUT);
  pinMode(speedA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(speedB, OUTPUT);

  // Setup servo
  head.attach(servo);
  //  testServo();

  // Setup buzzer
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);   // Turn OFF buzzer

  //  // Begin serial communication with PC at 9600 bps
  //  Serial.begin(9600);
}

void loop() {
  tsundereBot();
}

void lineTracker() {
  // Line Tracking Algorithm - Simple
  // Read all line tracking sensor modules
  int lineL = digitalRead(sensorL);
  int lineC = digitalRead(sensorC);
  int lineR = digitalRead(sensorR);

  // Group the sensor data into string form
  String lineState = String(lineL) + String(lineC) + String(lineR);

  if (lineState == "111") {
    moveForward();
  }
  else if (lineState == "110") {
    cornerRight();
  }
  else if (lineState == "101") {
    moveForward();
  }
  else if (lineState == "100") {
    cornerRight();
  }
  else if (lineState == "011") {
    cornerLeft();
  }
  else if (lineState == "010") {
    moveForward();
  }
  else if (lineState == "001") {
    cornerLeft();
  }
  else if (lineState == "000") {
    moveForward();
  }

  delay(50);
}

void beetleBot() {  // Beetlebot Algorithm
  // Get distance between sonar sensor and surface
  distance = averageDistance(echo, trig);

  if (distance > 10) {
    moveForward();
  }
  else if (distance < 5) {
    moveBackward();
  }
  else if (distance >= 5 && distance <= 10) {
    int moveDir = random(1, 2);
    noMove(); delay(500);

    if (moveDir == 1) {
      rotateLeft();
      delay(random(500, 1000));
    }
    else if (moveDir == 2) {
      rotateRight();
      delay(random(500, 1000));
    }
  }
}

void tsundereBot() {  // Tsundere robot algorithm
  head.write(100);

  // Get distance between sonar sensor and surface
  distance = averageDistance(echo, trig);

  if (distance > 20) {
    moveForward();
  }
  else if (distance >= 15 && distance <= 20) {
    noMove();
  }
  else if (distance < 15) {
    moveBackward();
  }
}
