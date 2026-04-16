// =============================================================================
//  LEDManager — Example 03: Active-Low LED
//  LEDManager — Przykład 03: LED z logiką odwróconą
// =============================================================================
//
//  For LEDs wired with cathode to 3.3V (active-low / logika odwrócona).
//  Common on dev boards with built-in LEDs (e.g. ESP32, ESP8266).
//  Typowe dla wbudowanych LED na płytkach deweloperskich.
//
//  Wiring / Podłączenie:
//    3.3V → LED anode → LED cathode → 220Ω → Pin 2
//
//  S.M. DIY Home | https://github.com/00Maciek00/libraries_LEDManager
// =============================================================================

#include <LEDManager.h>

#define LED_PIN 2

LEDManager leds;

void setup() {
    // activeHigh = false → LOW lights up / LOW świeci
    leds.addLED(LED_PIN, false);

    leds.setMode(LED_PIN, LED_BLINK);
}

void loop() {
    leds.update();
}
