#include <Arduino.h>
#include <KeyLed.h>

#define pinLed1 13
#define pinLed2 12

KeyLed led1(pinLed1);
KeyLed led2(pinLed2);

void setup() {
  led1.begin();
  led2.begin();
}

void loop() {
  
  led1.blink(250); // blink in freq 250 ms
  led2.blink(1000); // blin in freq 1000 ms or 1sec

  led1.loopLed();
  led2.loopLed();
}
