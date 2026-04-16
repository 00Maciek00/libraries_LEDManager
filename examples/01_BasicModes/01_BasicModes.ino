// =============================================================================
//  LEDManager — Example 01: Basic Modes
//  LEDManager — Przykład 01: Podstawowe tryby
// =============================================================================
//
//  Demonstrates: LED_ON, LED_OFF, LED_BLINK, LED_PULSE
//  Demonstruje:  LED_ON, LED_OFF, LED_BLINK, LED_PULSE
//
//  Wiring / Podłączenie:
//    Pin 2 → 220Ω → LED anode → LED cathode → GND
//
//  S.M. DIY Home | https://github.com/00Maciek00/libraries_LEDManager
// =============================================================================

#include <LEDManager.h>

#define LED_PIN 2

LEDManager leds;

void setup() {
    leds.addLED(LED_PIN);

    // Blink as status indicator / Miganie jako sygnał statusu
    leds.setMode(LED_PIN, LED_BLINK);
}

void loop() {
    leds.update();   // Must be called in every loop / Wymagane w każdym loop

    // Example: pulse on button press / Przykład: błysk na naciśnięcie przycisku
    // leds.pulse(LED_PIN);
}
