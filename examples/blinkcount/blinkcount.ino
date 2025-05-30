#include <Arduino.h>
#include <KeyLed.h>

KeyLed led(13);

void setup() {
  led.begin();
  led.blink(); //set blink with freq default 1sec
  led.setCountBlink(10); // blink 10 times and stop
}

void loop() {
  led.loopLed();
}
