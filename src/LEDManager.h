// =============================================================================
//  LEDManager — Non-blocking LED control library for Arduino
//  LEDManager — Biblioteka do nieblokującej obsługi LED dla Arduino
// =============================================================================
//
//  Version / Wersja: 1.2.0
//  Author / Autor:   Maciej Sikorski
//  Date / Data:      2026-04-14
//  Project / Projekt: S.M. DIY Home
//
//  Supported modes / Obsługiwane tryby:
//    LED_OFF              — off / zgaszona
//    LED_ON               — on continuously / świeci ciągle
//    LED_BLINK            — blink 300ms on/off / miganie 300ms
//    LED_PULSE            — single short flash 50ms / pojedynczy błysk 50ms
//    LED_ON_TIMED         — on for duration ms, then OFF / świeci przez duration ms, potem OFF
//    LED_BLINK_FAST_TIMED — fast blink 80ms for duration ms, then OFF
//                           szybkie miganie 80ms przez duration ms, potem OFF
//
//  Features / Cechy:
//    — Up to 8 LEDs / Do 8 diod LED
//    — Active-high and active-low logic / Logika normalna i odwrócona
//    — No blocking delays / Brak blokujących delay()
//    — No Serial dependency / Brak zależności od Serial
//
// =============================================================================
//  Changelog
// =============================================================================
//
//  v1.2.0 (2026-04-14)
//    - LED_ON_TIMED: on for duration ms, then OFF / świeci duration ms, potem OFF
//    - LED_BLINK_FAST_TIMED: fast blink for duration ms, then OFF
//      szybkie miganie przez duration ms, potem OFF
//    - setModeTimed(): set timed mode with duration / tryb timed z czasem trwania
//
//  v1.1.0
//    - addLED(pin, activeHigh): active-low support / obsługa logiki odwróconej
//    - writePin(): central write with activeHigh / centralny zapis z activeHigh
//    - setState(): logical on/off, not HIGH/LOW / logika świeci/gaśnie
//
//  v1.0.0
//    - Initial release / Pierwsza wersja
//
// =============================================================================
//  Copyright 2026 Maciej Sikorski — S.M. DIY Home
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// =============================================================================

#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

// Maximum number of managed LEDs / Maksymalna liczba obsługiwanych LED-ów
#define MAX_LEDS 8

// LED operating modes / Tryby pracy LED
enum LEDMode {
    LED_OFF,              // Off / Zgaszona
    LED_ON,               // On continuously / Zapalona ciągle
    LED_BLINK,            // Blink 300ms on/off / Miganie 300ms — dla statusu
    LED_PULSE,            // Single flash 50ms / Krótki błysk 50ms — dla zdarzeń
    LED_ON_TIMED,         // On for duration ms, then OFF / Świeci przez duration ms, potem OFF
    LED_BLINK_FAST_TIMED  // Fast blink 80ms for duration ms, then OFF
                          // Szybkie miganie 80ms przez duration ms, potem OFF
};

// Timing constants in milliseconds / Predefiniowane czasy w milisekundach
#define BLINK_INTERVAL       300   // Blink period for LED_BLINK / Czas migania
#define PULSE_DURATION        50   // Flash duration for LED_PULSE / Czas impulsu
#define BLINK_FAST_INTERVAL   80   // Blink period for LED_BLINK_FAST_TIMED / Czas szybkiego migania

// Internal state of a single LED / Struktura przechowująca stan pojedynczego LED
struct LEDState {
    uint8_t       pin;          // GPIO pin number / Numer pinu GPIO
    LEDMode       mode;         // Current operating mode / Aktualny tryb pracy
    bool          state;        // Logical state: true = on / Stan logiczny: true = świeci
    unsigned long lastChange;   // Timestamp of last state change / Czas ostatniej zmiany
    bool          active;       // Pin in use / Czy pin jest używany
    bool          activeHigh;   // true  = HIGH lights up (default) / HIGH świeci (domyślne)
                                // false = LOW lights up / LOW świeci (logika odwrócona)
    unsigned long duration;     // Timed mode duration ms, 0 = infinite / Czas trwania, 0 = nieskończony
    unsigned long modeStart;    // Timed mode start timestamp / Timestamp wejścia w tryb timed
};

class LEDManager {
private:
    LEDState leds[MAX_LEDS];
    uint8_t  ledCount;

    int8_t findLEDIndex(uint8_t pin);
    void   updateLED(LEDState& led);

    // Write logical state to pin respecting activeHigh
    // Zapis stanu logicznego na pin z uwzględnieniem activeHigh
    void   writePin(LEDState& led, bool logicalState);

public:
    LEDManager();

    // Add LED with active-high logic (HIGH = on) / Dodaj LED z logiką normalną (HIGH = świeci)
    bool addLED(uint8_t pin);

    // Add LED with explicit logic / Dodaj LED z jawnym określeniem logiki
    // activeHigh = true  → HIGH lights up, cathode to GND / HIGH świeci, katoda do GND
    // activeHigh = false → LOW lights up,  cathode to 3V3 / LOW świeci,  katoda do 3V3
    bool addLED(uint8_t pin, bool activeHigh);

    // Set LED operating mode / Ustaw tryb pracy LED
    void setMode(uint8_t pin, LEDMode mode);

    // Set timed mode — auto OFF after durationMs
    // Ustaw tryb z automatycznym wyłączeniem po durationMs
    // Intended for LED_ON_TIMED and LED_BLINK_FAST_TIMED
    // Przeznaczony dla LED_ON_TIMED i LED_BLINK_FAST_TIMED
    void setModeTimed(uint8_t pin, LEDMode mode, unsigned long durationMs);

    // Single short flash (PULSE) / Krótki błysk (PULSE)
    void pulse(uint8_t pin);

    // Main update function — call in loop() / Główna funkcja — wywołuj w loop()
    void update();

    // Force logical state: true = on, false = off / Wymuś stan logiczny: true = świeci
    // Respects activeHigh automatically / Uwzględnia activeHigh automatycznie
    void setState(uint8_t pin, bool logicalState);

    // Get current LED mode / Sprawdź aktualny tryb LED
    LEDMode getMode(uint8_t pin);
};

#endif // LED_MANAGER_H
