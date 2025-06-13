/*
  Biblioteca para utilizar com leds
  Dácio Braga - fdacio@gmail.com
  MIT License
*/
#include "KeyLed.h"

KeyLed::KeyLed(uint8_t pin) { 
  _pin = pin; 
  _sinInverse = false;
}

KeyLed::KeyLed(uint8_t pin, bool sinInverse) {
  _pin = pin;
  _sinInverse = sinInverse;
}

uint8_t KeyLed::getPin() { return _pin; }

bool KeyLed::getSignal(bool signal) {
  bool _signal = signal;
  if (_sinInverse) _signal = !signal;
  return _signal;
}

void KeyLed::begin() { 
  pinMode(_pin, OUTPUT); 
  _stateLed = getSignal(LOW);
}

void KeyLed::on() {
  _on = true;
  _off = false;
  _blink = false;
  _stateLed = getSignal(HIGH);
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
  _stateLed = getSignal(LOW);
}

void KeyLed::write(bool sin) {
  digitalWrite(_pin, getSignal(sin));
}

bool KeyLed::read() { return getSignal(digitalRead(_pin)); }

void KeyLed::stopBlink() {
  _blink = false;
  write(getSignal(LOW));
}

void KeyLed::blink() {
  _blink = true;
  _on = false;
  _off = false;
  _stateLed = getSignal(LOW);
}

void KeyLed::blink(unsigned int freqBlink) {
  _freqBlink = freqBlink;
  blink();
}

void KeyLed::setCountBlink(unsigned int count) {
  _countBlink = count;
  if (read() == getSignal(HIGH)) {
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
      _stateLed = getSignal(HIGH);
    } else if (_timeElapsed > _freqBlink) {
      _stateLed = getSignal(LOW);
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
      _stateLed = getSignal(LOW);
      _hasCountBlink = false;
      if (*_callBackCountBlink != NULL) {
        (*_callBackCountBlink)();
      }
    }

    write(getSignal(_stateLed));
  }

  if (_on) {
    // Verifica se tem um tempo para ficar On
    if (_timeOn > 0) {
      _timeElapsed = millis() - _timeStartOn;
      // Verificar se o tempo de ficar On passou
      if (_timeElapsed > _timeOn) {
        _timeStartOn = millis();
        _on = false;
        _stateLed = getSignal(LOW);
        if (*_callBackTimeOn != NULL) {
          (*_callBackTimeOn)();
        }
      }
    }
    write(getSignal(_stateLed));
  }

  if (_off) {
    write(getSignal(_stateLed));
  }
}
