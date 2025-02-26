#include <Arduino.h>
#include "FastLED.h"
#include "Player.h"

#define NUM_LEDS      100
#define LED_TYPE   WS2811
#define COLOR_ORDER   RGB
#define DATA_PIN       13

CRGBArray<NUM_LEDS> leds;
uint32_t lastTick = 0;

Player p1(34,39,36);
Player p2(25,33,32);

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);
}

void loop() {
  if (lastTick + 100 < millis()) {
    p1.pollPots();
    p2.pollPots();

    leds[0] = CRGB(0, 0, p1.valB);
    leds[1] = CRGB(0, p1.valG, 0);
    leds[2] = CRGB(p1.valR, 0, 0);

    leds[3] = CRGB(p1.valR, p1.valG, p1.valB);
    for (uint8_t i = 4; i < 9; i++) {
      leds[i] = leds[3];
    }

    leds[16] = CRGB(0, 0, p2.valB);
    leds[17] = CRGB(0, p2.valG, 0);
    leds[18] = CRGB(p2.valR, 0, 0);

    leds[19] = CRGB(p2.valR, p2.valG, p2.valB);
    for (uint8_t i = 20; i < 26; i++) {
      leds[i] = leds[19];
    }

    // bundle
    leds[9] = leds[3] + leds[19];
    for (uint8_t i = 10; i < 16; i++) {
      leds[i] = leds[9];
    }
    
    FastLED.show();
    lastTick = millis();
  }
}
