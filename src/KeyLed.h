/*
  Biblioteca para utilizar com leds
  Dácio Braga - fdacio@gmail.com
  MIT License
*/

#ifndef KeyLed_h
#define KeyLed_h

#include <Arduino.h>

class KeyLed {
public:
  /**
    pin : number pin
  */
  KeyLed(uint8_t pin);
  /**
    pin : number pin
    sinInverse : HIGH off led, LOW on led
  */
  KeyLed(uint8_t pin, bool sinInverse);
  uint8_t getPin();
  void begin();
  void loopLed();
  void on();
  void on(unsigned int timeOn);
  void setCallbackTimeOn(void (*callbackTimeOn)(void));
  void off();
  void write(bool sin);
  bool read();
  void blink();
  void blink(unsigned int freqBlink);
  void stopBlink();
  void setCountBlink(unsigned int count);
  void setCallBackCountBlink(void (*callbackCountBlink)(void));
private:
  uint8_t _pin;
  bool _sinInverse = false;
  bool getSignal(bool state);
  bool _stateLed = LOW;
  bool _blink = false;
  bool _on = false;
  bool _off = false;
  unsigned long _millisBlink = 0;
  unsigned int _freqBlink = 500;
  unsigned int _timeBlink = 0;
  unsigned int _timeOn = 0;
  unsigned long _timeStartBlink = 0;
  unsigned long _timeStartOn = 0;
  unsigned long _timeElapsed = 0;
  void (*_callBackTimeOn)(void) = NULL;
  void (*_callBackCountBlink)(void) = NULL;
  unsigned int _countBlink = 0;
  bool _hasCountBlink = false;
};

#endif
