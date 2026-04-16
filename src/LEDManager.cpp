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

#include "LEDManager.h"

// ── Constructor / Konstruktor ─────────────────────────────────────────────────
LEDManager::LEDManager() {
    ledCount = 0;
    for (uint8_t i = 0; i < MAX_LEDS; i++) {
        leds[i].active     = false;
        leds[i].pin        = 0;
        leds[i].mode       = LED_OFF;
        leds[i].state      = false;
        leds[i].lastChange = 0;
        leds[i].activeHigh = true;
        leds[i].duration   = 0;
        leds[i].modeStart  = 0;
    }
}

// ── writePin() — central write respecting activeHigh ─────────────────────────
// ── writePin() — centralny zapis z uwzględnieniem activeHigh ─────────────────
void LEDManager::writePin(LEDState& led, bool logicalState) {
    led.state = logicalState;
    digitalWrite(led.pin, (logicalState == led.activeHigh) ? HIGH : LOW);
}

// ── addLED() — default active-high logic / domyślna logika normalna ───────────
bool LEDManager::addLED(uint8_t pin) {
    return addLED(pin, true);
}

// ── addLED(pin, activeHigh) ───────────────────────────────────────────────────
bool LEDManager::addLED(uint8_t pin, bool activeHigh) {
    if (ledCount >= MAX_LEDS)   return false;
    if (findLEDIndex(pin) >= 0) return false;

    leds[ledCount].pin        = pin;
    leds[ledCount].active     = true;
    leds[ledCount].mode       = LED_OFF;
    leds[ledCount].state      = false;
    leds[ledCount].lastChange = millis();
    leds[ledCount].activeHigh = activeHigh;
    leds[ledCount].duration   = 0;
    leds[ledCount].modeStart  = 0;

    pinMode(pin, OUTPUT);
    writePin(leds[ledCount], false);   // OFF on start / OFF przy starcie

    ledCount++;
    return true;
}

// ── findLEDIndex() ────────────────────────────────────────────────────────────
int8_t LEDManager::findLEDIndex(uint8_t pin) {
    for (uint8_t i = 0; i < MAX_LEDS; i++) {
        if (leds[i].active && leds[i].pin == pin) return i;
    }
    return -1;
}

// ── setMode() ─────────────────────────────────────────────────────────────────
void LEDManager::setMode(uint8_t pin, LEDMode mode) {
    int8_t index = findLEDIndex(pin);
    if (index < 0) return;

    LEDState& led = leds[index];
    if (led.mode == mode) return;

    led.mode       = mode;
    led.lastChange = millis();
    led.duration   = 0;
    led.modeStart  = 0;

    switch (mode) {
        case LED_OFF:              writePin(led, false); break;
        case LED_ON:               writePin(led, true);  break;
        case LED_BLINK:            writePin(led, true);  break;
        case LED_PULSE:            writePin(led, true);  break;
        case LED_ON_TIMED:         writePin(led, true);  break;
        case LED_BLINK_FAST_TIMED: writePin(led, true);  break;
    }
}

// ── setModeTimed() ────────────────────────────────────────────────────────────
void LEDManager::setModeTimed(uint8_t pin, LEDMode mode, unsigned long durationMs) {
    int8_t index = findLEDIndex(pin);
    if (index < 0) return;

    LEDState& led  = leds[index];
    led.mode       = mode;
    led.duration   = durationMs;
    led.modeStart  = millis();
    led.lastChange = led.modeStart;

    switch (mode) {
        case LED_ON_TIMED:         writePin(led, true);  break;
        case LED_BLINK_FAST_TIMED: writePin(led, true);  break;
        default:                   writePin(led, false); break;
    }
}

// ── pulse() ───────────────────────────────────────────────────────────────────
void LEDManager::pulse(uint8_t pin) {
    setMode(pin, LED_PULSE);
}

// ── updateLED() ───────────────────────────────────────────────────────────────
void LEDManager::updateLED(LEDState& led) {
    unsigned long now     = millis();
    unsigned long elapsed = now - led.lastChange;

    switch (led.mode) {
        case LED_OFF:
        case LED_ON:
            break;

        case LED_BLINK:
            if (elapsed >= BLINK_INTERVAL) {
                writePin(led, !led.state);
                led.lastChange = now;
            }
            break;

        case LED_PULSE:
            if (elapsed >= PULSE_DURATION) {
                writePin(led, false);
                led.mode       = LED_OFF;
                led.lastChange = now;
            }
            break;

        case LED_ON_TIMED:
            if (led.duration > 0 && (now - led.modeStart) >= led.duration) {
                writePin(led, false);
                led.mode       = LED_OFF;
                led.lastChange = now;
            }
            break;

        case LED_BLINK_FAST_TIMED:
            if (led.duration > 0 && (now - led.modeStart) >= led.duration) {
                writePin(led, false);
                led.mode       = LED_OFF;
                led.lastChange = now;
            } else if (elapsed >= BLINK_FAST_INTERVAL) {
                writePin(led, !led.state);
                led.lastChange = now;
            }
            break;
    }
}

// ── update() — call in loop() / wywołuj w loop() ──────────────────────────────
void LEDManager::update() {
    for (uint8_t i = 0; i < MAX_LEDS; i++) {
        if (leds[i].active) updateLED(leds[i]);
    }
}

// ── setState() — logical on/off / logika świeci/gaśnie ───────────────────────
void LEDManager::setState(uint8_t pin, bool logicalState) {
    int8_t index = findLEDIndex(pin);
    if (index < 0) return;
    writePin(leds[index], logicalState);
}

// ── getMode() ─────────────────────────────────────────────────────────────────
LEDMode LEDManager::getMode(uint8_t pin) {
    int8_t index = findLEDIndex(pin);
    if (index < 0) return LED_OFF;
    return leds[index].mode;
}
