CRGB *bl_palette;

CRGB *bl_ledTarget;
CRGB *bl_leds;
int bl_ledCount;

CRGB bl_twinkleColor = 0;
byte bl_twinkleChance = 0;
int bl_twinkleSustainTime = 300;
long *bl_twinkleTimes;

uint8_t bl_timePeriod = 40; //0; //(x/4)Hz or 0 for no effect.
uint8_t bl_timeAmplitude = 255; // 0 = no effect, 255 ~= 12 times speed difference between slowest and fastest.
uint8_t bl_timePhase = 0; //

long _time = 0;
long _wallTime = 0;

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
  long prevWallTime = _wallTime;
  _wallTime = millis();
  int wallTimeStep = (int) (_wallTime - prevWallTime);

  long timeSineAdj = 128*255; //meaning use wallTime as-is
  uint8_t amplitudeMultiple;
  if (bl_timePeriod) {
    //              0-256              -128-128   0-256
    timeSineAdj = (bl_timeAmplitude * (128 - sin8((uint8_t) (_wallTime / bl_timePeriod) + bl_timePhase)) / 64) + 128
    //timeSineAdj is between z -> 256 where z = 256/multiple
//    byte z = 256L * 16 / bl_timeAmplitude;
//    timeSineAdj = ((long) z * 255 + (256L - z) * sin8((uint8_t) (_wallTime / bl_timePeriod) + bl_timePhase)) / (128L - z);
    //20 ->240 ish
//    timeSineAdj = (20L + (5L * bl_timeAmplitude * (sin8((uint8_t) (_wallTime / bl_timePeriod) + bl_timePhase)) / 6) / 255);
  }
  long prevTime = _time;
  _time = prevTime + (long) wallTimeStep * timeSineAdj / 256;
  int timeStep = _time - prevTime;

  //

  Serial.print(_wallTime);
  Serial.print("\t");
  Serial.print(wallTimeStep);
  Serial.print("\t");
  Serial.print(timeSineAdj);
  Serial.print("\t");
  Serial.print(timeSineAdj / 256);
  Serial.print("\t");
  Serial.print(_time);
  Serial.print("\t");
  Serial.print(timeStep);
  Serial.println("");

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



