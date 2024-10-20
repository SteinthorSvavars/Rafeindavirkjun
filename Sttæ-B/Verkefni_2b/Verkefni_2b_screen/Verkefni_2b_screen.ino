// Steinþór Emil
// skjástýring

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DEBUG_MODE  

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  lcd.begin();
  lcd.print("Hello world!");
  delay(2000);

#ifdef DEBUG_MODE
  // Virkir debug mode með því að skoða samsetningu skipunar
  Serial.begin(9600);
  Wire.begin();
  debugI2CScanner();
#endif
}

void loop() 
{
  //main 
}

#ifdef DEBUG_MODE
void debugI2CScanner() 
{
  Serial.println("leitar að I2C tækjum");
  
  byte error, address;
  int deviceCount = 0;
  
  for (address = 1; address < 127; address++) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) 
    {
      Serial.print("I2C tæki fundið á addressuni 0x");
      if (address < 16) 
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      deviceCount++;
    }
  }
  
  if (deviceCount == 0) 
  {
    Serial.println("ekkert I2C tæki fundið.");
  } 
  else 
  {
    Serial.println("I2C leit kláruð");
    Serial.print("Fjöldi tækja fundin: ");
    Serial.println(deviceCount);
  }
}
#endif
