#ifdef ESP32
#include <Arduino.h>
#else
#include <avr/io.h>
#include <util/delay.h>
#endif

const int PWM_PIN = 9;  // PWM output pin
const int RESISTOR_PIN = A0;  // Analog input pin to read resistor value
const int SLEEP_TIME = 5000;  // Time to sleep in milliseconds

void setup() {
  pinMode(PWM_PIN, OUTPUT);
#ifdef ESP32
  analogWriteFrequency(PWM_PIN, 10000);  // Set PWM frequency to 10 kHz
#endif
}

void loop() {
  // Read resistor value and map it to PWM duty cycle
  int resistor_value = analogRead(RESISTOR_PIN);
  int duty_cycle = map(resistor_value, 0, 1023, 0, 255);

  // Set PWM duty cycle
#ifdef ESP32
  ledcWrite(PWM_CHANNEL, duty_cycle);  // For ESP32
#else
  analogWrite(PWM_PIN, duty_cycle);  // For Arduino
#endif

  // Put processor to sleep
#ifdef ESP32
  esp_sleep_enable_timer_wakeup(SLEEP_TIME * 1000);  // Convert to microseconds for ESP32
  esp_deep_sleep_start();
#else
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  _delay_ms(SLEEP_TIME);  // For Arduino
#endif
}
