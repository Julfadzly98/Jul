#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
#include <Servo.h>

const char* ssid = "smartspacekk";
const char* password = "smartspace09";

const char BotToken[] = "885754931:AAHGG90q5SgrVWJMbBYNzVsswXXMFBH1W20" ;

//607773461:AAHnZKLOvtziggLN7IzpHRZXPyRdZmroVgE

Servo myservo;
WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);


const int servoPin = 16; //D0
//const int buttonPin = 12;
//const int ledPin = 13;

String text_message;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for the Serial monitor to be opened

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  myservo.attach(servoPin);
  //pinMode(buttonPin, INPUT);
  //digitalWrite(buttonPin, HIGH);
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  myservo.write(180);
  delay(1000);
  myservo.detach();

   bot.begin();
}

void loop() {
  //int buttonVal = digitalRead(buttonPin);
  //if(buttonVal == LOW) {
  message m = bot.getUpdates(); 
  if (m.text.equals("stop")) 
  {
    myservo.attach(servoPin);
    myservo.write(30);
    delay(575);
    myservo.write(180);
    delay(1500);
    myservo.detach();
    delay(5000);
    bot.sendMessage(m.chat_id, "Servo is working");
  }

  else if (m.text.equals("on")) 
  {
    myservo.attach(servoPin);
    myservo.write(360);
    delay(500);
    //myservo.write(180);
    //delay(1500);
    //myservo.detach();
    //delay(5000);
    bot.sendMessage(m.chat_id, "Servo is working");
  }
  else if
 
  delay(13);
  
}
