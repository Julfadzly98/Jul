#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 2          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "bmAvkICScAbZYHziVtJoKibZFAmo-zZM";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "nodemcu";
char pass[] = "esp8266_";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{  
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if ( t >= 28 ) {
     Blynk.notify("WARNING");
    }
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
