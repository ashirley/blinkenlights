CRGB *bl_palette;

CRGB *bl_ledTarget;
CRGB *bl_leds;
int bl_ledCount;

CRGB bl_twinkleColor = 0;
byte bl_twinkleChance = 0;
int bl_twinkleSustainTime = 300;
long *bl_twinkleTimes;

long _time = 0;

void blinken_init(CRGB *palette, CRGB* leds, int ledCountIn) {
  bl_palette = palette;
  bl_ledCount = ledCountIn;
  bl_leds = leds;
  bl_ledTarget = (CRGB *) malloc(ledCountIn * sizeof(CRGB));
  bl_twinkleTimes = (long *) malloc(ledCountIn * sizeof(long));
  memset(bl_twinkleTimes, 0, ledCountIn * sizeof(long));
  _time = millis();

  //set the max refresh rate to at least 20 Hz or lower if already set.
  FastLED.setMaxRefreshRate(20, true);
}

/**
 * set the twinkle effect.
 * 
 * @param color The color to flash
 * @param chance There is a n/255 chance of a twinkle in any given led in 1000 time steps
 */
void blinken_setTwinkle(CRGB color, byte chance) {
  bl_twinkleColor = color;
  bl_twinkleChance = chance;
}


void blinken_show() {
  //advance time
  long prevTime = _time;
  _time = millis();
  int timeStep = (int) (_time - prevTime);

  for (byte i = 0; i < bl_ledCount; i++) {
    //twinkle?
    if (bl_twinkleChance && (random16() <= ((long) bl_twinkleChance * 256 * timeStep / 1000))) {
      bl_twinkleTimes[i] = _time;
    }

    bl_ledTarget[i] = bl_palette[0];

    if (_time - bl_twinkleTimes[i] <= bl_twinkleSustainTime) {
      bl_leds[i] = bl_twinkleColor;
    }
    else {
      //fade towards target
      bl_leds[i] = bl_leds[i].scale8(64) + bl_ledTarget[i].scale8(192); // 3/4 target + 1/4 curr.
    }
  }
  FastLED.show();
  delay(30);
}



