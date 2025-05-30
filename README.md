# KeyLed

Uma biblioteca para controle de LEDs no Arduino com funcionalidades avançadas como:

- Piscar com frequência definida
- Ligar/desligar com tempo programado
- Callbacks após eventos
- Suporte a lógica invertida

## Instalação

Repositório https://github.com/fdacio/KeyLed
Baixe o arquivo zip
Instale no Arduino IDE

## Exemplo básico

```cpp
#include <KeyLed.h>

KeyLed led(13);

void setup() {
  led.begin();
  led.blink(500);
}

void loop() {
  led.loopLed();
}

## Métodos disponíveis

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
