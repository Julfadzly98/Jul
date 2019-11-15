
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Light A0

char auth[] = "f6d5e9927af84a48913a8a447ddcb885";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "smartspacekk";
char pass[] = "smartspace09";

int light_value;
int light;


void setup() {
  Serial.begin(112500);
  pinMode(Light, INPUT); //data pin for ambientlight sensor
  pinMode(13, OUTPUT);
 
}

void loop() {
  int light_value = analogRead(Light);
  light = light_value * 0.0976;// percentage calculation 
  Serial.println(light);
  delay(100);
  if (light_value > 1000) {
    digitalWrite(13, HIGH);
  }
  else {digitalWrite(13,LOW);}
 Blynk.virtualWrite(V5, light);
 Blynk.run();
}
