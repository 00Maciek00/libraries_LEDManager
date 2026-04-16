// =============================================================================
//  LEDManager — Example 02: Timed Modes
//  LEDManager — Przykład 02: Tryby czasowe
// =============================================================================
//
//  Demonstrates: LED_ON_TIMED, LED_BLINK_FAST_TIMED
//  Demonstruje:  LED_ON_TIMED, LED_BLINK_FAST_TIMED
//
//  LED on pin 2 lights for 2 seconds, then turns off.
//  LED on pin 3 blinks fast for 1 second, then turns off.
//
//  LED na pinie 2 świeci 2 sekundy, potem gaśnie.
//  LED na pinie 3 miga szybko przez 1 sekundę, potem gaśnie.
//
//  S.M. DIY Home | https://github.com/00Maciek00/libraries_LEDManager
// =============================================================================

#include <LEDManager.h>

#define LED_A 2
#define LED_B 3

LEDManager leds;

void setup() {
    leds.addLED(LED_A);
    leds.addLED(LED_B);

    // On for 2000ms, then auto OFF / Świeci 2000ms, potem automatycznie OFF
    leds.setModeTimed(LED_A, LED_ON_TIMED, 2000);

    // Fast blink for 1000ms, then auto OFF / Szybkie miganie 1000ms, potem OFF
    leds.setModeTimed(LED_B, LED_BLINK_FAST_TIMED, 1000);
}

void loop() {
    leds.update();
}
