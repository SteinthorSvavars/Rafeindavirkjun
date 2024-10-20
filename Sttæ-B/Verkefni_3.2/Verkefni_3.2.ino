#include <WiFi.h>
#include <Preferences.h>

#define INPUT_PIN 4       
#define LOG_INTERVAL 10   // stillir hversu of það er loggað á kubbinn

Preferences preferences;

void setup() {
  Serial.begin(115200);
  pinMode(INPUT_PIN, INPUT);
  preferences.begin("input_log", false); // setur preferences sem "input_log"
}

void loop() {
  static unsigned long last_log_time = 0;
  unsigned long current_time = millis();

  if (current_time - last_log_time >= LOG_INTERVAL * 1000) {
    last_log_time = current_time;
    int input_status = digitalRead(INPUT_PIN);
    preferences.putBool("status", (bool)input_status); // geymir inputið í preferences 'input_log'
    Serial.print("Input status: ");
    Serial.println(input_status);
  }
}
