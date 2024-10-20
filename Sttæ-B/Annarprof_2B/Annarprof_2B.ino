#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX | TX

int ledPin = 13;
int blinkRate = 500; // default blink rate in milliseconds
int blinkCount = 0; // variable to count the number of blinks

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  // check if there is data available on the Bluetooth module
  if (BTSerial.available() > 0) {
    int sliderValue = BTSerial.parseInt();
    // set the blink rate based on the slider value received
    blinkRate = map(sliderValue, 0, 1023, 100, 1000);
  }

  digitalWrite(ledPin, HIGH); // turn on the LED
  delay(blinkRate); // wait for the blink rate
  digitalWrite(ledPin, LOW); // turn off the LED
  blinkCount++; // increment the blink count

  // print the blink count to the Serial monitor when the LED is off
  if (digitalRead(ledPin) == LOW) {
    Serial.println("Blink count: " + String(blinkCount));
  }
}
