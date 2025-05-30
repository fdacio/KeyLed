#include <Arduino.h>
#include <KeyLed.h>

KeyLed led(13);

void setup() {
  led.begin();
}

void loop() {
  led.write(!led.read());
  delay(1000);
}
