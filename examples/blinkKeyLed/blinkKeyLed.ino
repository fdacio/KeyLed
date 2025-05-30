#include <Arduino.h>
#include <KeyLed.h>

#define pinLed 13

KeyLed led(pinLed);

void setup() {
  led.begin();
  led.blink(); //freq default 1sec.
}

void loop() {
  led.loopLed(); //without delay function
}
