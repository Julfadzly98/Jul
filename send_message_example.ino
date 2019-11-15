//#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define SECRET_SSID "00"
#define SECRET_PASS "12345678"
#define SECRET_BOT_TOKEN "607773461:AAHnZKLOvtziggLN7IzpHRZXPyRdZmroVgE"
#define IR D7

// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;
// Initialize Telegram BOT
const char BotToken[] = SECRET_BOT_TOKEN;

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);

int detection;
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

  pinMode(IR, INPUT);
  bot.begin();
}

void loop() {
  detection = digitalRead(IR);

  if (detection == 0) 
  {
    text_message = "Ada barang";
  } 
  else 
  {
    text_message = "Tiada barang";
  }

  message m = bot.getUpdates(); // Read new messages
  Serial.println(m.chat_id);
  if ( m.chat_id != 0) {
    bot.sendMessage(m.chat_id, text_message);
  }

  delay(1000);
}
