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
  blinken_setTwinkle(CRGB::White, 20);
  Serial.begin(115200);
  Serial.println("Startup");
}

void loop() {
  blinken_show();
}

