#include <Arduino.h>
#include "FastLED.h"
#include "library.h"

#define NUM_LEDS 200
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

CRGB palette[2] = {0x0000ff, 0xffffff};

CRGB christmas[] = {0xFF7400, 0xFF6400, 0xFF3700, 0xFF1300, 0xFF0000, 0xDA7A00, 0xDA8F00, 0xC98F00, 0xC96400, 0xAE7A00, 0x697A00, 0x287A00, 0x28B800, 0x28B800, 0x28B800, 0x28B800, 0x47D021, 0x47DF3D, 0x0CFF34, 0x47F421, 0x47F421, 0x47ED3D, 0x47EA3D, 0x27DD3D, 0x0CD15B, 0x0CD181, 0x0CD1B2, 0x0CD1CC, 0x0CFFD6, 0x0CDCEB, 0x0CC9EB, 0x0CA3EB, 0x006BFF, 0x156BFF, 0x596BFF, 0x7C6BFF, 0x884DFF, 0xAF3CC3, 0xAF3C75, 0xC33C40, 0xC3090C, 0xFF090C, 0xFF090C, 0xFF180C, 0xFF4A0C, 0xFF710C, 0xFF820C, 0xFFAA0C, 0xFFFA0C, 0xFFAA0C};
const int christmasCount = 50;

byte heart[] = { 0x00, 0x0A, 0x29, 0x25, 0x1B, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x26, 0x26, 0x1C, 0x02, 0x00, 0x0D, 0x57, 0x7A, 0x75, 0x55, 0x15, 0x00, 0x00, 0x00, 0x09, 0x53, 0x77, 0x82, 0x60, 0x12, 0x00, 0x31, 0x76, 0x35, 0x30, 0x5E, 0x59, 0x0A, 0x00, 0x09, 0x4A, 0x86, 0x5B, 0x5B, 0x8C, 0x51, 0x06, 0x4D, 0x75, 0x0F, 0x01, 0x24, 0x7A, 0x3C, 0x19, 0x41, 0x6B, 0x3F, 0x0A, 0x0E, 0x69, 0x87, 0x0F, 0x5D, 0x7E, 0x11, 0x00, 0x09, 0x5C, 0x83, 0x95, 0x7A, 0x2A, 0x04, 0x00, 0x08, 0x5C, 0x88, 0x12, 0x53, 0x6E, 0x22, 0x03, 0x00, 0x0D, 0x3A, 0x53, 0x38, 0x02, 0x00, 0x00, 0x03, 0x3E, 0x69, 0x0C, 0x21, 0x56, 0x55, 0x23, 0x02, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x01, 0x22, 0x5C, 0x3D, 0x05, 0x06, 0x2E, 0x63, 0x58, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 0x39, 0x75, 0x4D, 0x0F, 0x00, 0x00, 0x05, 0x20, 0x58, 0x6E, 0x2A, 0x05, 0x00, 0x00, 0x12, 0x4C, 0x6F, 0x47, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x4E, 0x6C, 0x49, 0x12, 0x2F, 0x72, 0x86, 0x41, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x40, 0x88, 0x7E, 0x8F, 0x5B, 0x21, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x2D, 0x59, 0x33, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//Location ledLocations[] = {Location(1, 1), Location(1, 2), Location(1, 3), Location(1, 4), Location(1, 5), Location(1, 6), Location(1, 7), Location(1, 8), Location(1, 9), Location(1, 10), Location(1, 11), Location(1, 12), Location(1, 13), Location(1, 14), Location(1, 15), Location(1, 16), Location(1, 17), Location(1, 18), Location(1, 19), Location(1, 20), Location(1, 21), Location(1, 22), Location(1, 23), Location(1, 24), Location(2, 24), Location(3, 24), Location(4, 24), Location(4, 23), Location(4, 22), Location(4, 21), Location(4, 20), Location(4, 19), Location(4, 18), Location(4, 17), Location(4, 16), Location(4, 15), Location(4, 14), Location(4, 13), Location(4, 12), Location(4, 11), Location(4, 10), Location(4, 9), Location(4, 8), Location(4, 7), Location(4, 6), Location(4, 5), Location(4, 4), Location(4, 3), Location(4, 2), Location(4, 1)};
Location ledLocations[] = {Location(1, 1), Location(1, 2), Location(1, 3), Location(1, 4), Location(1, 5), Location(1, 6), Location(1, 7), Location(1, 8), Location(1, 9), Location(1, 10), Location(1, 11), Location(1, 12), Location(2, 12), Location(2, 11), Location(2, 10), Location(2, 9), Location(2, 8), Location(2, 7), Location(2, 6), Location(2, 5), Location(2, 4), Location(2, 3), Location(2, 2), Location(2, 1), Location(3, 1), Location(3, 2), Location(3, 3), Location(3, 4), Location(3, 5), Location(3, 6), Location(3, 7), Location(3, 8), Location(3, 9), Location(3, 10), Location(3, 11), Location(3, 12), Location(4, 12), Location(4, 11), Location(4, 10), Location(4, 9), Location(4, 8), Location(4, 7), Location(4, 6), Location(4, 5), Location(4, 4), Location(4, 3), Location(4, 2), Location(4, 1), Location(5, 1), Location(5, 2), Location(5, 3), Location(5, 4), Location(5, 5), Location(5, 6), Location(5, 7), Location(5, 8), Location(5, 9), Location(5, 10), Location(5, 11), Location(5, 12), Location(6, 12), Location(6, 11), Location(6, 10), Location(6, 9), Location(6, 8), Location(6, 7), Location(6, 6), Location(6, 5), Location(6, 4), Location(6, 3), Location(6, 2), Location(6, 1), Location(7, 1), Location(7, 2), Location(7, 3), Location(7, 4), Location(7, 5), Location(7, 6), Location(7, 7), Location(7, 8), Location(7, 9), Location(7, 10), Location(7, 11), Location(7, 12), Location(8, 12), Location(8, 11), Location(8, 10), Location(8, 9), Location(8, 8), Location(8, 7), Location(8, 6), Location(8, 5), Location(8, 4), Location(8, 3), Location(8, 2), Location(8, 1), Location(9, 1), Location(9, 2), Location(9, 3), Location(9, 4), Location(9, 5), Location(9, 6), Location(9, 7), Location(9, 8), Location(9, 9), Location(9, 10), Location(9, 11), Location(9, 12), Location(10, 12), Location(10, 11), Location(10, 10), Location(10, 9), Location(10, 8), Location(10, 7), Location(10, 6), Location(10, 5), Location(10, 4), Location(10, 3), Location(10, 2), Location(10, 1), Location(11, 1), Location(11, 2), Location(11, 3), Location(11, 4), Location(11,5), Location(11, 6), Location(11, 7), Location(11, 8), Location(11, 9), Location(11, 10), Location(11, 11), Location(11, 12), Location(12, 12), Location(12, 11), Location(12, 10), Location(12, 9), Location(12, 8), Location(12, 7), Location(12, 6), Location(12, 5), Location(12, 4), Location(12, 3), Location(12, 2), Location(12, 1), Location(13, 1), Location(13, 2), Location(13, 3), Location(13, 4), Location(13,5), Location(13, 6), Location(13, 7), Location(13, 8), Location(13, 9), Location(13, 10), Location(13, 11), Location(13, 12), Location(14, 12), Location(14, 11), Location(14, 10), Location(14, 9), Location(14, 8), Location(14, 7), Location(14, 6), Location(14, 5), Location(14, 4), Location(14, 3), Location(14, 2), Location(14, 1), Location(15, 1), Location(15, 2), Location(15, 3), Location(15, 4), Location(15,5), Location(15, 6), Location(15, 7), Location(15, 8), Location(15, 9), Location(15, 10), Location(15, 11), Location(15, 12), Location(16, 12), Location(16, 11), Location(16, 10), Location(16, 9), Location(16, 8), Location(16, 7), Location(16, 6), Location(16, 5), Location(16, 4), Location(16, 3), Location(16, 2), Location(16, 1)};

void setup() {
  Serial.begin(115200);
  Serial.println("Startup");

  Serial.print("Initialising FastLED...");
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  Serial.println(" Done");
  Serial.print("Initialising random seeds...");
  randomSeed(analogRead(0));
  random16_set_seed(analogRead(0));
  Serial.println(" Done");

  Serial.print("Initialising LED array...");
  FastLED.setBrightness(64);
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  Serial.println(" Done");

  Serial.print("Showing first LED values...");
  FastLED.show();
  Serial.println(" Done");

  Serial.print("initialising blinken...");
  blinken_init(christmas, christmasCount, leds, NUM_LEDS);
  Serial.println(" Done");

  Serial.print("setting blinken locations...");
  blinken_setLocations(ledLocations);
  Serial.println(" Done");

  Serial.print("setting blinken locations...");
  blinken_setMask(255, 16, heart);
  Serial.println(" Done");

  Serial.print("setting blinken twinkle...");
  blinken_setTwinkle(CRGB::White, 20);
  Serial.println(" Done");
}

void loop() {
  blinken_show();
}
