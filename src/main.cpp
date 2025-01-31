#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS      100
#define LED_TYPE   WS2811
#define COLOR_ORDER   GRB
#define DATA_PIN       13

#define RED_POT_PIN    34
#define GREEN_POT_PIN  39
#define BLUE_POT_PIN   36

CRGBArray<NUM_LEDS> leds;
uint32_t lastTick = 0;
uint8_t hue = 0;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);
}

void loop() {
  if (lastTick + 100 < millis()) {
    uint8_t red = map(analogRead(RED_POT_PIN), 0, 4095, 0, 255);
    uint8_t green = map(analogRead(GREEN_POT_PIN), 0, 4095, 0, 255);
    uint8_t blue = map(analogRead(BLUE_POT_PIN), 0, 4095, 0, 255);
    Serial.print(" red: ");
    Serial.print(red);
    Serial.print(" green: ");
    Serial.print(green);
    Serial.print(" blue: ");
    Serial.println(blue);
    leds.fill_solid(CRGB(red, green, blue));
    FastLED.show();
    lastTick = millis();
  }
}
