/*
  Biblioteca para utilizar com leds
  Dácio Braga - fdacio@gmail.com
  MIT License
*/
#include "KeyLed.h"


KeyLed::KeyLed(uint8_t pin) { _pin = pin; }


KeyLed::KeyLed(uint8_t pin, bool sinInverse) {
  _pin = pin;
  _sinInverse = sinInverse;
}

uint8_t KeyLed::getPin() { return _pin; }

void KeyLed::begin() { pinMode(_pin, OUTPUT); }

void KeyLed::on() {
  _on = true;
  _off = false;
  _blink = false;
  _stateLed = LOW;
}

void KeyLed::on(unsigned int timeOn) { 
  _timeOn = timeOn; 
  on();
}

void KeyLed::setCallbackTimeOn(void (*callBackTimeOn)(void)) {
  _callBackTimeOn = callBackTimeOn;
}

void KeyLed::off() {
  _off = true;
  _on = false;
  _blink = false;
  _stateLed = LOW;
}

void KeyLed::write(bool sin) {
  bool _sin = (_sinInverse) ? !sin : sin;
  digitalWrite(_pin, _sin);
}

bool KeyLed::read() { return digitalRead(_pin); }

void KeyLed::stopBlink() {
  _blink = false;
  write(LOW);
}

void KeyLed::blink() {
  _blink = true;
  _on = false;
  _off = false;
  _stateLed = LOW;
}

void KeyLed::blink(unsigned int freqBlink) {
  _freqBlink = freqBlink;
  blink();
}

void KeyLed::setCountBlink(unsigned int count) {
  _countBlink = count;
  if (read() == HIGH) {
    _countBlink++;
  }
  _hasCountBlink = true;
}

void KeyLed::setCallBackCountBlink(void (*callBackCountBlink)(void)) {
  _callBackCountBlink = callBackCountBlink;
}

void KeyLed::loopLed() {

  if (_blink) {

    _timeElapsed = millis() - _millisBlink;

    if (_timeElapsed < _freqBlink) {
      _stateLed = HIGH;
    } else if (_timeElapsed > _freqBlink) {
      _stateLed = LOW;
    }

    // reset _millisBlink apos passar o tempo da frequencia
    if (_timeElapsed > (_freqBlink * 2)) {
      _millisBlink = millis();
      if (_hasCountBlink)
        _countBlink--;
    }

    // verfica a quantidade de blink
    if (_hasCountBlink && _countBlink == 0) {
      _blink = false;
      _stateLed = LOW;
      _hasCountBlink = false;

      if (*_callBackCountBlink != NULL) {
        (*_callBackCountBlink)();
      }
    }

    write(_stateLed);
  }

  if (_on && !_blink) {
    _timeElapsed = millis() - _timeStartOn;
    if (_timeOn > 0 && _timeElapsed > _timeOn) {
      _timeStartOn = millis();
      _on = false;
      _stateLed = !_stateLed;
      if (*_callBackTimeOn != NULL) {
        (*_callBackTimeOn)();
      }
    }
    write(_stateLed);
  }

  if (_off && !_blink) {
    write(_stateLed);
  }
}
