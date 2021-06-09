/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#define TRIGGER D1
#define ECHO    D2

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bmAvkICScAbZYHziVtJoKibZFAmo-zZM";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "nodemcu";
char pass[] = "esp8266_";
void setup() {
  
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

   if (distance <= 50) {
    Blynk.notify("PENUH");
}
  else {
    //Blynk.notify("NOTHING");
  }



  
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  Blynk.virtualWrite(V0, distance);
  delay(200);
  Blynk.run();
}
