#include <Arduino.h>
#include <KeyLed.h>

KeyLed led(13);
void myFunction();

void setup() {
  Serial.begin(9600);
  led.begin();
  led.blink(); //freq default 1sec
  led.setCountBlink(10); // blink 10 times and stop
  led.setCallBackCountBlink(myFunction); // sets the function that will be called after the count blink
}

void loop() {
  led.loopLed();
}

void myFunction() {
  Serial.println("call my function");
  //Here your logic
}