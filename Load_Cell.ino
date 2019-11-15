#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#include <HX711_ADC.h>

//HX711 constructor (dout pin, sck pin)
HX711_ADC LoadCell(A1, A0);

long t;

int tetap = 100;

//******************** Ubah Nilai Barang Disini Sahaje **************************************
float HargaBarang = 0.0028;   //2.80 dibahagikan 1000 untuk dapat kan harga setiap 1 gram  **
//*******************************************************************************************

void setup() {
  Serial.begin(9600);
  lcd.begin();              
  lcd.backlight();

  
  lcd.setCursor(3,0);
  lcd.print("Eksa Smart ");
  lcd.setCursor(2,1);
  lcd.print("Recycle Bin");
  delay(1000);
  
  Serial.println("Wait...");
  LoadCell.begin();
  long stabilisingtime = 2000; 
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(696.0); 
  Serial.println("Startup + tare is complete");


  lcd.clear();
  
}

void loop() 
{
  LoadCell.update();

  if (Serial.available() > 0) {
    float i;
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  //check if last tare operation is complete
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }


    float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    t = millis();
    
    
if(i>1000)
{
    float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    t = millis();
    float ii = i/1000;
    lcd.setCursor(1,0);
    lcd.print("Weight:");
    lcd.setCursor(8,0);
    lcd.print(ii);
    lcd.print("         ");
    lcd.setCursor(12,0);
    lcd.print("kg");
        
    float w = i*HargaBarang;
    Serial.println(w);

    lcd.setCursor(5,1);
    lcd.print("RM:");
    lcd.setCursor(8,1);
    lcd.print(w);
    lcd.print("          ");
 
   
      delay(1000);
}
    
else
{
  float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    t = millis();
    
    lcd.setCursor(1,0);
    lcd.print("Weight:");
    lcd.setCursor(8,0);
    lcd.print(i);
    lcd.print("         ");
    lcd.setCursor(14,0);
    lcd.print("g");
   
    

      if(i <= 5.00)
     {
      i=0.00;
      lcd.setCursor(8,0);
      lcd.print(i);
      lcd.print("        ");
     
     }
     
    float w = i*HargaBarang;
    Serial.println(w);

    lcd.setCursor(5,1);
    lcd.print("RM:");
    lcd.setCursor(8,1);
    lcd.print(w);
    
    lcd.print("          ");

       if(i <= 1.00)
     {
      i=0.00;
      lcd.setCursor(8,0);
      lcd.print(i);
      lcd.setCursor(13,0);
      lcd.print("g");
      lcd.print("        ");
     
     }
   
      delay(1000);
}
     
}
