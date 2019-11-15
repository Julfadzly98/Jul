#include "pitches.h"

// =======================================================================
// Distance Range Finding
// =======================================================================

int sonarAverage = 5;

// To get more accurate distance reading, use sonarAverage
// to read sensor several times, then average the reading
float averageDistance(int _echo, int _trig) {
  float _distance[sonarAverage];
  float _averageDistance = 0;

  for (int i = 0; i < sonarAverage; i++) {
    _distance[i] = sonarRead(_echo, _trig);
    _averageDistance += _distance[i];
    delay(10);
  }

  _averageDistance /= sonarAverage;

  return _averageDistance;
}

// Direct acquire the distance reading from HC-SR04
float sonarRead(int _echoPin, int _trigPin) {
  float _duration;
  float _cm, _in;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(5);

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  _duration = pulseIn(_echoPin, HIGH);

  // convert the time into a distance
  _cm = (_duration / 2.0) / 29.1;     // Get distance in cm
  //  _in = (_duration / 2) / 74;       // Get distance in inch

  return _cm;
}

// =======================================================================
// Robot Motion Control
// =======================================================================

void moveForward() {
  digitalWrite(dirA, HIGH);
  analogWrite(speedA, 255 - MTSPEED);
  digitalWrite(dirB, HIGH);
  analogWrite(speedB, 255 - MTSPEED);
}

void moveBackward() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, MTSPEED);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, MTSPEED);
}

void rotateLeft() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, MTSPEED);
  digitalWrite(dirB, HIGH);
  analogWrite(speedB, 255 - MTSPEED);
}

void rotateRight() {
  digitalWrite(dirA, HIGH);
  analogWrite(speedA, 255 - MTSPEED);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, MTSPEED);
}

void cornerLeft() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, MTSPEED / 2);
  digitalWrite(dirB, HIGH);
  analogWrite(speedB, 255 - MTSPEED);
}

void cornerRight() {
  digitalWrite(dirA, HIGH);
  analogWrite(speedA, 255 - MTSPEED);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, MTSPEED / 2);
}

void steerLeft() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, 0);
  digitalWrite(dirB, HIGH);
  analogWrite(speedB, 255 - MTSPEED);
}

void steerRight() {
  digitalWrite(dirA, HIGH);
  analogWrite(speedA, 255 - MTSPEED);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, 0);
}

void RsteerLeft() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, 0);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, MTSPEED);
}

void RsteerRight() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, MTSPEED);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, 0);
}

void noMove() {
  digitalWrite(dirA, LOW);
  analogWrite(speedA, 0);
  digitalWrite(dirB, LOW);
  analogWrite(speedB, 0);
}

// =======================================================================
// Head Servo Test
// =======================================================================


void testServo() {
  // Test Servo Motor
  head.write(88);
  delay(1000);
  head.write(180);
  delay(1000);
  head.write(88);
  delay(1000);
  head.write(0);
  delay(1000);
  head.write(88);
  delay(1000);

  beep();
}

// =======================================================================
// Buzzer Beep Note
// =======================================================================

// notes in the melody:
int beep1[] = {
  NOTE_C4, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 2
};

void beep() {
  for (int thisNote = 0; thisNote < 2; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(3, beep1[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(3);
  }
}
