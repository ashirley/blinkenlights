#include <Arduino.h>
#include "FastLED.h"
#include "library.h"

#define NUM_LEDS 50
#define DATA_PIN 6

#define NUM_LEDS2 120
#define DATA_PIN2 7

CRGB leds[NUM_LEDS + NUM_LEDS2];

CRGB palette[2] = {0x0000ff, 0xffffff};

CRGB christmas[] = {0xFF7400, 0xFF6400, 0xFF3700, 0xFF1300, 0xFF0000, 0xDA7A00, 0xDA8F00, 0xC98F00, 0xC96400, 0xAE7A00, 0x697A00, 0x287A00, 0x28B800, 0x28B800, 0x28B800, 0x28B800, 0x47D021, 0x47DF3D, 0x0CFF34, 0x47F421, 0x47F421, 0x47ED3D, 0x47EA3D, 0x27DD3D, 0x0CD15B, 0x0CD181, 0x0CD1B2, 0x0CD1CC, 0x0CFFD6, 0x0CDCEB, 0x0CC9EB, 0x0CA3EB, 0x006BFF, 0x156BFF, 0x596BFF, 0x7C6BFF, 0x884DFF, 0xAF3CC3, 0xAF3C75, 0xC33C40, 0xC3090C, 0xFF090C, 0xFF090C, 0xFF180C, 0xFF4A0C, 0xFF710C, 0xFF820C, 0xFFAA0C, 0xFFFA0C, 0xFFAA0C};
const int christmasCount = 50;

Location ledLocations[] = {Location(1, 1), Location(2, 1), Location(3, 1), Location(4, 1), Location(5, 1), Location(6, 1), Location(7, 1), Location(8, 1), Location(9, 1), Location(10, 1), Location(11, 1), Location(12, 1), Location(13, 1), Location(14, 1), Location(15, 1), Location(16, 1), Location(17, 1), Location(18, 1), Location(19, 1), Location(20, 1), Location(21, 1), Location(22, 1), Location(23, 1), Location(24, 1), Location(24, 2), Location(24, 3), Location(24, 4), Location(23, 4), Location(22, 4), Location(21, 4), Location(20, 4), Location(19, 4), Location(18, 4), Location(17, 4), Location(16, 4), Location(15, 4), Location(14, 4), Location(13, 4), Location(12, 4), Location(11, 4), Location(10, 4), Location(9, 4), Location(8, 4), Location(7, 4), Location(6, 4), Location(5, 4), Location(4, 4), Location(3, 4), Location(2, 4), Location(1, 4)};

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds + 50, NUM_LEDS2);
  randomSeed(analogRead(0));
  random16_set_seed(analogRead(0));

  FastLED.setBrightness(64);
  for (byte i = 0; i < NUM_LEDS/* + NUM_LEDS2*/; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();

  blinken_init(christmas, 50, leds, NUM_LEDS/* + NUM_LEDS2*/);
  blinken_setLocations(ledLocations);
  blinken_setTwinkle(CRGB::White, 20);
  Serial.begin(115200);
  Serial.println("Startup");
}

void loop() {
  blinken_show();
}

