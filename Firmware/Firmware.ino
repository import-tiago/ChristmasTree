#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 13

#define DATA_PIN 6

CRGB LEDs[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);
  LEDs[0] = CRGB::Red;
  LEDs[1] = CRGB::Red;
  LEDs[2] = CRGB::Red;
  LEDs[3] = CRGB::Red;
  LEDs[4] = CRGB::Red;
  LEDs[5] = CRGB::Red;
  LEDs[6] = CRGB::Red;
  LEDs[7] = CRGB::Red;
  LEDs[8] = CRGB::Red;
  LEDs[9] = CRGB::Red;
  LEDs[10] = CRGB::Red;
  LEDs[11] = CRGB::Red;
 // LEDs[12] = CRGB::Red;
  FastLED.setBrightness( 15 );
  LEDs[12] = CRGB::Yellow;
  //FastLED.setBrightness( 60 );
  FastLED.show();
}

void loop() {

}
