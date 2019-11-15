#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define Red 5
#define Green 16

const char* ssid = "smartspacekk";
const char* password = "smartspace09";

const char BotToken[] = "607773461:AAHnZKLOvtziggLN7IzpHRZXPyRdZmroVgE";

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);

void setup()
{
    Serial.begin(9600);
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

  bot.begin();
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  
}
void loop() 
{  
  message m = bot.getUpdates(); // Read new messages  
  if (m.text.equals("on")) 
  {     
   digitalWrite(Red,HIGH); //Red on
   delay(1000);
   digitalWrite(Green,LOW); //Green off
   delay(1000); //Wait half a second
   digitalWrite(Red,LOW); //Red off
   delay(1000);
   digitalWrite(Green,HIGH); //Green on
   delay(1000); //Wait half a second
    
    bot.sendMessage(m.chat_id, "LED is ON");
    Serial.println("LED is ON");  
  }  
  
  else if (m.text.equals("off")) 
  {  
    digitalWrite(Red, LOW);   
    digitalWrite(Green, LOW); 
    bot.sendMessage(m.chat_id, "LED is OFF");  
    Serial.println("LED is OFF");
  } 
}
