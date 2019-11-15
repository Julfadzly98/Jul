#include <LiquidCrystal.h>
int buzzer = 7;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16, 2);
pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(A0);
delay(500);
Serial.println(sensorValue);
lcd.print("Speed =");
lcd.print(sensorValue);
lcd.println("            ");
lcd.setCursor(0,0);
if (sensorValue > 300)
{
  digitalWrite(buzzer, HIGH);
}
else if (sensorValue < 300)
{
  digitalWrite(buzzer, LOW);
}
}
