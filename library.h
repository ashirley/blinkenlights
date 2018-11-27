CRGB *bl_ledTarget;
CRGB *bl_leds;
int bl_ledCount;

//*****
// LEDs show colors from a palette which rotates over time

CRGB *bl_palette;
int bl_paletteCount;
int bl_palettePeriod = 10; //time to cycle through the whole palette

//*****
// LEDs can "twinkle" i.e. randomly change quickly to this color then slowly back (typically CRGB::White )

CRGB bl_twinkleColor = 0;
byte bl_twinkleChance = 0;
int bl_twinkleSustainTime = 100;
long *bl_twinkleTimes;

//*****
// Time itself can progress faster/slower based on a sine wave.

uint8_t bl_timePeriod = 40; //0; //(x/4)Hz or 0 for no effect.
uint8_t bl_timeAmplitude = 64; // 0 = no effect, 255 ~= 12 times speed difference between slowest and fastest.
uint8_t bl_timePhase = 0; //

//*****
// Things can vary by the location of the LED to create spatial effects

struct Location {
  int x;
  int y;

  Location(int xi, int yi) {
    x = xi;
    y = yi;
  }
};
Location *bl_ledLocations;
byte bl_paletteX = 64; // 1 means offset palette 1 position for every 16 leds.
byte bl_paletteY = 16; // 16 means 1 palette offset per led and 255 means 16 offest per led.

//*****
// Things can vary according to a mask or image

byte bl_maskAmount = 0;
byte bl_maskRowLength;
byte *bl_mask;


long _time = 0;
long _wallTime = 0;

void blinken_init(CRGB *palette, int paletteCount, CRGB* leds, int ledCountIn) {
  bl_palette = palette;
  bl_paletteCount = paletteCount;
  bl_leds = leds;
  bl_ledCount = ledCountIn;
  bl_ledTarget = (CRGB *) malloc(ledCountIn * sizeof(CRGB));
  bl_twinkleTimes = (long *) malloc(ledCountIn * sizeof(long));
  memset(bl_twinkleTimes, 0, ledCountIn * sizeof(long));
  _time = millis();

  //set the max refresh rate to at least 20 Hz or lower if already set.
  FastLED.setMaxRefreshRate(20, true);
}

void blinken_setLocations(Location* locations) {
  bl_ledLocations = locations;
}

void blinken_setMask(byte amount, byte rowLength, byte* mask) {
  bl_mask = mask;
  bl_maskRowLength = rowLength;
  bl_maskAmount = amount;
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

  //Work out how much actual time (wall time) has passed.
  //Then use a sine wave to determine how much of that wallTime change we will add onto our virtual time.
  // TODO: When we apply this effect we speed time up on average which I would prefer to avoid
  // also, there is a discontinuity on the graph of speed of time which is upsetting!

  long prevWallTime = _wallTime;
  _wallTime = millis();
  int wallTimeStep = (int) (_wallTime - prevWallTime);

  long timeSineAdj = 128*255; //meaning use wallTime as-is
  if (bl_timePeriod) {
    //a: sin is 0->255 (128 is neutral)
    // b: -128, multiply by (bl_timeAmplitude / 64) (0->4), + 512 = 0->1024 (512 is neutral)
    // 0    means use 1/4 * wallTimeStep
    // 256  means use 1/2 * wallTimeStep
    // 512  means use  1  * wallTimeStep
    // 768  means use  2  * wallTimeStep
    // 1024 means use  4  * wallTimeStep

    int a = sin8((uint8_t) (_wallTime / bl_timePeriod) + bl_timePhase);
    int b = (bl_timeAmplitude * (a - 128) / 64) + 512;
    //TODO: Can this be done mathmatically?
    if (b == 512) {
      timeSineAdj = 512; // / 512
    } else if (b < 512) {
      timeSineAdj = 128 + (3L * 128 * b / 512);// / 512  //between 512 and 128
    } else {
      timeSineAdj = (b - 512) * 3 + 512;// / 512
    }
  }

  long prevTime = _time;
  _time = prevTime + (long) wallTimeStep * timeSineAdj / 512;
  int timeStep = _time - prevTime;

  int paletteIndex;
  for (byte i = 0; i < bl_ledCount; i++) {
    //twinkle?
    if (bl_twinkleChance && (random16() <= ((long) bl_twinkleChance * 256 * timeStep / 1000))) {
      bl_twinkleTimes[i] = _time;
    }

    paletteIndex = map(((_time / (bl_palettePeriod)) % 1024), 0, 1023, 0, bl_paletteCount);

    int locationOffset = 0;
    if (bl_paletteX || bl_paletteY) {
      locationOffset = (bl_ledLocations[i].x * bl_paletteX + bl_ledLocations[i].y * bl_paletteY) / 16;
    }

    int maskOffset = 0;
    if (bl_maskAmount) {
      Location loc = bl_ledLocations[i];
      maskOffset = bl_mask[loc.x * bl_maskRowLength + loc.y] * bl_maskAmount / 16;
    }

    paletteIndex = (paletteIndex + locationOffset + maskOffset) % bl_paletteCount;
    bl_ledTarget[i] = bl_palette[paletteIndex];

    if (_time - bl_twinkleTimes[i] <= bl_twinkleSustainTime) {
      bl_leds[i] = bl_twinkleColor;
    }
    else {
      //fade towards target
      bl_leds[i] = bl_leds[i].nscale8(128) + bl_ledTarget[i].nscale8(128); // 1/2 target + 1/2 curr.
    }
  }

  FastLED.show();
  delay(30);
}



