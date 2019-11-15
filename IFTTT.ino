#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#define IR D7

int detection = HIGH;
int status = WL_IDLE_STATUS; //not required.

const char* ssid = "iot";
const char* password = "0168187199";
int doorClosed = 1;

void setup() {
  pinMode(IR,INPUT);

  Serial.begin(9600);

  setupWifi();
   
   //get_http();

}

void setupWifi()
{
     // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
   WiFi.mode(WIFI_STA);
   status = WiFi.begin(ssid, password);    

   Serial.print("Attempting to connect to SSID: ");
   Serial.println(ssid);  

   // Wait for connection
   while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
   }
   Serial.println("Connected to wifi");
}

void loop() {
   if (WiFi.status() != WL_CONNECTED)
   {
     setupWifi();
   }
  // put your main code here, to run repeatedly:
  detection = digitalRead(IR);
  if(detection == LOW)
  {
    Serial.print("The Mail is there");
    while (get_http(String("The_Mail_is_there")) != 0);
  }
  else{ 
    Serial.print("No obstacle!\n");
    while (get_http(String("No_Mail")) != 0);
  }
  delay(500);    


}


int get_http(String state)
{
   HTTPClient http;
   int ret = 0;
   Serial.print("[HTTP] begin...\n");
   // configure ifttt server and url  should be HTTP only..not https!!!  (http://)   
    http.begin("https://maker.ifttt.com/trigger/Mail/with/key/iBVDqCytg1lH0_AxXp_0gzNGdWFkXpsgKk0ySbsB8NA"); //HTTP
   //If you have enabled value1 from iftt settings then uncomment below line to send value and comment out above line  
   //http.begin("http://maker.ifttt.com/trigger/door/with/key/your_key_from_Iftt/?value1="+state); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
        ret = -1;
        Serial.printf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        delay(500); // wait for half sec before retry again
    }

    http.end();
    return ret;
}  
