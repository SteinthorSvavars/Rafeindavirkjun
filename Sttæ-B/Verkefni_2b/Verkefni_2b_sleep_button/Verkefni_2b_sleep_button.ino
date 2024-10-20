#include <esp_deep_sleep.h>

const int buttonPin = 2;  //Pinni fyrir takkan

void setup() 
{
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  
  //Stillir "vaknadur" frá hnappi
  esp_sleep_enable_ext0_wakeup((gpio_num_t)buttonPin, LOW); 
  
  //Fer í djúpsvefn
  Serial.println("Fer í djúpsvefn...");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() 
{
  //Þessi kóði er aldrei keyrður þar sem ESP32 fer í Deep sleep strax eftir setup()
}