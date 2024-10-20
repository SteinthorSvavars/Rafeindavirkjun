#include <esp_sleep.h>

const int wakeUpPin = GPIO_NUM_13;  //Pinni til að vekja á ESP32
const int readPin = GPIO_NUM_14;   //Pinni til að lesa skynjaragildið
const int serialBaudRate = 9600;   //Serial baud hlutfall

void setup() 
{
  pinMode(wakeUpPin, INPUT_PULLUP);  //Stillir WakeUPPin sem ingang með innri pull-up viðnámi
  pinMode(readPin, INPUT);

  Serial.begin(serialBaudRate);
  delay(100);  //Gefur tíma fyrir serial til að frumstilla
  Serial.println("ESP32 fer nú að sofa...");
  Serial.flush();

  esp_sleep_enable_ext0_wakeup(wakeUpPin, LOW);
  esp_deep_sleep_start();
}

void loop() 
{
  //Þessi kóði verður ekki keyrður þar sem ESP32 fer aftur að sofa eftir að hafa vaknað
}