# KeyLed

Uma biblioteca para controle de LEDs no Arduino com funcionalidades avançadas como:

- Piscar com frequência definida
- Ligar/desligar com tempo programado
- Callbacks após eventos
- Suporte a lógica invertida

## Instalação

Coloque a pasta `KeyLed` na pasta `libraries` do seu Arduino.

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
