#include <Arduino.h>
#include <EEPROM.h>

const int analogPin = A0;  //Analog pinni tengdur við NTC hitaviðnámi
const int fanPin = 9;  // Pinninn sem er tengdur í vistuna 
const int thresholdTemperature = 35;  // Skilgreining á max hita í celsíus

const float R1 = 10000.0;  //Viðnáms gildi fasta viðnámsins í spennudeilinum
const float referenceTemperature = 25.0;  //Viðmiðunarhitastig í celsíus
const float beta = 3950.0;  //Beta gildi NTC Hitaviðnámsins

bool temperatureExceededFlag = false;  //Flag til að gefa til kynna hvort hitastig fer yfir viðmiðunar hitastig

void setup() 
{
  pinMode(fanPin, OUTPUT);  //Stillir viftupinna sem útgang
  Serial.begin(9600);  //Frumstillir serial samskiptin
}

void loop() 
{
  int temperature = readTemperature();  //Les hitastig af NTC hitaviðnámi

  if (temperature > thresholdTemperature) 
  {
    temperatureExceededFlag = true;  // tékkar hvort hitin sé yfir mörkum
    saveFlagToFlashMemory();  // Skrifar hvað flaggið segir í flash
  }

  controlFan(temperature);  //Stýrir viftunni út frá hitastigi

  // Skrifar út hitastig og hvað flaggið segir í serial
  Serial.print("Hitastig: ");
  Serial.print(temperature);
  Serial.print("°C\Hitastig yfir flaggi: ");
  Serial.println(temperatureExceededFlag);

  delay(1000);  //Delay í 1 sek
}

float readTemperature() 
{
  int analogValue = analogRead(analogPin);  //Les analog gildi frá NTC hitaviðnáminu

  float voltage = (analogValue / 1023.0) * 5.0;  //Breytir analog gildinu í spennu (miðað við 5V viðmiðun)
  float resistance = (R1 * voltage) / (5.0 - voltage);  //Reiknar Viðnám á NTC hitaviðnáminu

  float steinhart;
  steinhart = resistance / R1;  //Reiknar hlutfallið R/R0
  steinhart = log(steinhart); 
  steinhart /= beta;
  steinhart += 1.0 / (referenceTemperature + 273.15);  
  steinhart = 1.0 / steinhart;  
  steinhart -= 273.15;  //Breytir yfir í Celcius

  return steinhart;
}

void controlFan(float temperature) 
{
  if (temperature <= thresholdTemperature) 
  {
    analogWrite(fanPin, 255);  // Setur viftuna á max
  } 
  else 
  {
    analogWrite(fanPin, 0);  //Slekkur á viftuni
  }
}

void saveFlagToFlashMemory() 
{
  EEPROM.write(0, temperatureExceededFlag);  //Skrifar hvað flaggið segur í flash í addressuna 0
  EEPROM.commit();  //Vistar flash
}