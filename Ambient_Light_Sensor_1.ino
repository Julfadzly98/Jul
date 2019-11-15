#define light A0 // define input pin

void setup() {
  // TEMT6000 Roboajx.com code
  Serial.begin(57600);
  
}

void loop() {
   // TEMT6000 Roboajx.com code
  int Lvalue = analogRead(light);// read the light
  int mVolt = map(Lvalue,0, 1023, 0, 5000);// map analogue reading to 5000mV
  float volt =(double)mVolt/1000;// convert millivolt to volt

  Serial.print(mVolt);// print millivolt
  Serial.print( "mV ");
  Serial.print(volt,3);// print volts with 3 decimal places
  Serial.println( "V ");
  delay(1000);// wait for 1000 milliseconds
   // TEMT6000 Roboajx.com code

} 
