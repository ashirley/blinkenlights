#include "FastLED.h"
#include "library.h"

#define NUM_LEDS 50
#define DATA_PIN 6

#define NUM_LEDS2 120
#define DATA_PIN2 7

CRGB leds[NUM_LEDS + NUM_LEDS2];

CRGB palette[2] = {0x0000ff, 0xffffff};

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds + 50, NUM_LEDS2);
  randomSeed(analogRead(0));
  random16_set_seed(analogRead(0));
  
  FastLED.setBrightness(64);
  for (byte i = 0; i < NUM_LEDS/* + NUM_LEDS2*/; i++) {
    leds[i] = CRGB::Black;
  }

  blinken_init(palette, leds, NUM_LEDS/* + NUM_LEDS2*/);
  blinken_setTwinkle(CRGB::White, 20);
  Serial.begin(115200);
  Serial.println("Startup");
}

void loop() {
  blinken_show();
}

