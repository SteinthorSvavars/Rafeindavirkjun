#include <TouchSensor.h>

#define TOUCH_PIN 4     // Touch sensor pinni
#define LED_PIN 2       // LED pinni

TouchSensor touch(TOUCH_PIN); // skilgreinir touch_pin sem snerti sensor
bool ledOn = false;

void setup() {
  pinMode(LED_PIN, OUTPUT); // Tilgreinir að led_pin sé output
}

void loop() {
  if (touch.isTouched()) {
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    delay(500); // það er smá delay til þess að passa að ledið er á í smá stund ef það er snert pinnan snöglega
  }
}
