# LEDManager


[Polski](#polski) | [English](#english)

---

## Polski

Biblioteka do zarządzania wieloma diodami LED jednocześnie, bez blokowania pętli programu. Zamiast `delay()` używa znaczników czasu — wszystkie diody działają niezależnie i równolegle.

---

## Funkcje

- Obsługa do 8 diod LED jednocześnie
- Tryby: ON, OFF, BLINK, PULSE, ON_TIMED, BLINK_FAST_TIMED
- Tryby czasowe z automatycznym wyłączeniem po zadanym czasie
- Obsługa logiki normalnej (HIGH świeci) i odwróconej (LOW świeci)
- Brak blokujących `delay()`
- Brak zależności od `Serial`
- Kompatybilność ze wszystkimi architekturami Arduino

---

## Tryby pracy

| Tryb | Opis |
|---|---|
| `LED_OFF` | Zgaszona |
| `LED_ON` | Świeci ciągle |
| `LED_BLINK` | Miganie 300ms on/off — sygnalizacja statusu |
| `LED_PULSE` | Pojedynczy błysk 50ms — sygnalizacja zdarzenia |
| `LED_ON_TIMED` | Świeci przez N ms, potem automatycznie OFF |
| `LED_BLINK_FAST_TIMED` | Szybkie miganie 80ms przez N ms, potem OFF |

---

## Struktura repozytorium

```
LEDManager/
├── README.md
├── LICENSE
├── keywords.txt
├── library.properties
├── src/
|   ├── LEDManager.h
|   └── LEDManager.cpp
└── examples/
    ├── 01_BasicModes/
    │   └── 01_BasicModes.ino
    ├── 02_TimedModes/
    │   └── 02_TimedModes.ino
    └── 03_ActiveLow/
        └── 03_ActiveLow.ino
```

---

## Instalacja

**Arduino IDE:**
1. Pobierz repozytorium jako ZIP
2. Sketch → Include Library → Add .ZIP Library
3. `#include <LEDManager.h>`

**Ręcznie:**  
Skopiuj `LEDManager.h` i `LEDManager.cpp` do folderu projektu.

---

## Szybki start

```cpp
#include <LEDManager.h>

LEDManager leds;

void setup() {
    leds.addLED(2);              // Zarejestruj LED na pinie 2
    leds.setMode(2, LED_BLINK); // Ustaw tryb migania
}

void loop() {
    leds.update();               // Wywołuj w każdym loop()
}
```

---

## Podłączenie

**Logika normalna** (domyślna, katoda do GND):
```
Pin → 220Ω → LED(+) → LED(-) → GND
```

**Logika odwrócona** (katoda do 3.3V, typowe dla wbudowanych LED na płytkach deweloperskich):
```
3.3V → LED(+) → LED(-) → 220Ω → Pin
```

---

## API

### `addLED(pin)` / `addLED(pin, activeHigh)`
Rejestruje diodę LED na podanym pinie GPIO.  
`activeHigh = true` → HIGH świeci (domyślne, katoda do GND)  
`activeHigh = false` → LOW świeci (katoda do 3.3V)

### `setMode(pin, mode)`
Ustawia tryb pracy diody.

### `setModeTimed(pin, mode, durationMs)`
Ustawia tryb czasowy — dioda automatycznie gaśnie po `durationMs` ms.  
Przeznaczony dla `LED_ON_TIMED` i `LED_BLINK_FAST_TIMED`.

### `pulse(pin)`
Pojedynczy błysk 50ms — przydatny do sygnalizacji zdarzeń.

### `setState(pin, state)`
Wymusza stan logiczny: `true` = świeci, `false` = gaśnie.  
Uwzględnia `activeHigh` automatycznie.

### `getMode(pin)`
Zwraca aktualny tryb pracy diody.

### `update()`
Główna funkcja biblioteki — wymagana w każdym `loop()`.

---

## Konfiguracja

Stałe czasowe można dostosować w pliku `LEDManager.h`:

| Stała | Wartość domyślna | Opis |
|---|---|---|
| `MAX_LEDS` | 8 | Maksymalna liczba obsługiwanych LED |
| `BLINK_INTERVAL` | 300 ms | Okres migania dla `LED_BLINK` |
| `PULSE_DURATION` | 50 ms | Czas błysku dla `LED_PULSE` |
| `BLINK_FAST_INTERVAL` | 80 ms | Okres szybkiego migania |

---

## Licencja

Copyright 2026 Maciej Sikorski — S.M. DIY Home  
Licencja Apache 2.0. Szczegóły w pliku [LICENSE](LICENSE).

---

**Wersja:** 1.2.0  
**Autor:** Maciej Sikorski 

**Projekt:** S.M. DIY Home  
**Data:** 2026-04-15  
**Licencja:** Apache 2.0

---
---

## English

A library for controlling multiple LEDs simultaneously without blocking the main program loop. Instead of `delay()`, it uses timestamps — all LEDs operate independently and in parallel.

---

## Features

- Control up to 8 LEDs simultaneously
- Modes: ON, OFF, BLINK, PULSE, ON_TIMED, BLINK_FAST_TIMED
- Timed modes with automatic OFF after a set duration
- Active-high (HIGH = on) and active-low (LOW = on) logic support
- No blocking `delay()`
- No `Serial` dependency
- Compatible with all Arduino architectures

---

## Operating Modes

| Mode | Description |
|---|---|
| `LED_OFF` | Off |
| `LED_ON` | On continuously |
| `LED_BLINK` | Blink 300ms on/off — status indicator |
| `LED_PULSE` | Single flash 50ms — event indicator |
| `LED_ON_TIMED` | On for N ms, then auto OFF |
| `LED_BLINK_FAST_TIMED` | Fast blink 80ms for N ms, then auto OFF |

---

## Repository Structure

```
LEDManager/
├── README.md
├── LICENSE
├── keywords.txt
├── library.properties
├── src/
|   ├── LEDManager.h
|   └── LEDManager.cpp
└── examples/
    ├── 01_BasicModes/
    │   └── 01_BasicModes.ino
    ├── 02_TimedModes/
    │   └── 02_TimedModes.ino
    └── 03_ActiveLow/
        └── 03_ActiveLow.ino
```

---

## Installation

**Arduino IDE:**
1. Download the repository as ZIP
2. Sketch → Include Library → Add .ZIP Library
3. `#include <LEDManager.h>`

**Manual:**  
Copy `LEDManager.h` and `LEDManager.cpp` into your project folder.

---

## Quick Start

```cpp
#include <LEDManager.h>

LEDManager leds;

void setup() {
    leds.addLED(2);              // Register LED on pin 2
    leds.setMode(2, LED_BLINK); // Set blink mode
}

void loop() {
    leds.update();               // Must be called in every loop()
}
```

---

## Wiring

**Active-high (default, cathode to GND):**
```
Pin → 220Ω → LED(+) → LED(-) → GND
```

**Active-low (cathode to 3.3V, common on dev boards with built-in LEDs):**
```
3.3V → LED(+) → LED(-) → 220Ω → Pin
```

---

## API

### `addLED(pin)` / `addLED(pin, activeHigh)`
Register an LED on the given GPIO pin.  
`activeHigh = true` → HIGH lights up (default, cathode to GND)  
`activeHigh = false` → LOW lights up (cathode to 3.3V)

### `setMode(pin, mode)`
Set the LED operating mode.

### `setModeTimed(pin, mode, durationMs)`
Set a timed mode — LED turns OFF automatically after `durationMs` ms.  
Intended for `LED_ON_TIMED` and `LED_BLINK_FAST_TIMED`.

### `pulse(pin)`
Single 50ms flash — useful for event signaling.

### `setState(pin, state)`
Force logical state: `true` = on, `false` = off.  
Respects `activeHigh` automatically.

### `getMode(pin)`
Returns the current LED mode.

### `update()`
Core library function — must be called in every `loop()`.

---

## Configuration

Timing constants can be adjusted in `LEDManager.h`:

| Constant | Default | Description |
|---|---|---|
| `MAX_LEDS` | 8 | Maximum number of managed LEDs |
| `BLINK_INTERVAL` | 300 ms | Blink period for `LED_BLINK` |
| `PULSE_DURATION` | 50 ms | Flash duration for `LED_PULSE` |
| `BLINK_FAST_INTERVAL` | 80 ms | Fast blink period |

---

## License

Copyright 2026 Maciej Sikorski — S.M. DIY Home  
Licensed under Apache 2.0. See [LICENSE](LICENSE) for details.

---

**Version:** 1.2.0  
**Author:** Maciej Sikorski  
**Project:** S.M. DIY Home  
**Date:** 2026-04-15  
**License:** Apache 2.0
