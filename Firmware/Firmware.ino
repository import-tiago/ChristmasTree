/* sinelon

   By: Mark Kriegsman

   Modified by: Andrew Tuline

   Adapted by: Tiago Silva (2020)

   This uses the built in beat in FastLED to move a dot back and forth. In this case, it uses two beats added together for more randomness.

*/

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define NUM_LEDS 13
#define DATA_PIN 6

#define LDR_PIN A0
#define LIGHT_LEVEL 750

CRGB leds[NUM_LEDS];

// Global variables can be changed on the fly.
uint8_t max_bright = 64;                                      // Overall brightness definition. It can be changed on the fly.

CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND

// Define variables used by the sequences.
uint8_t thisbeat =  23;                                       // Beats per minute for first part of dot.
uint8_t thatbeat =  28;                                       // Combined the above with this one.
uint8_t thisfade =   32;                                       // How quickly does it fade? Lower = slower fade rate.
uint8_t  thissat = 255;                                       // The saturation, where 255 = brilliant colours.
uint8_t  thisbri = 255;                                       // Brightness of a sequence.
int        myhue =   0;

int    thisdelay = 50;



void setup() {
  
  Serial.begin(9600);
  
  pinMode(LDR_PIN, INPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  currentBlending = LINEARBLEND;

  FastLED.setBrightness(max_bright);
  FastLED.setMaxPowerInVoltsAndMilliamps(3, 500);               // FastLED Power management set at 5V, 500mA.

} // setup()



void loop () {

  long Current_Light_Level = 0;
  for (int i = 0; i < 100; i++) {
    Current_Light_Level += analogRead(LDR_PIN);
  }
  Current_Light_Level /= 100;  
  Serial.println(Current_Light_Level);

  thisbri = Current_Light_Level / 4;

  if (thisbri < 30)
    thisbri = 30;

  //Serial.println(thisbri);
  if (Current_Light_Level < LIGHT_LEVEL) {

    EVERY_N_MILLISECONDS(50) {
      uint8_t maxChanges = 35;
      nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    }

    EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
      static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
      targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
    }

    EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
      sinelon();                                                // Call our sequence.
    }

    FastLED.show();
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }
}

void sinelon() {                                              // a colored dot sweeping back and forth, with fading trails

  fadeToBlackBy( leds, NUM_LEDS, thisfade);
  int pos1 = beatsin16(thisbeat, 0, NUM_LEDS);
  int pos2 = beatsin16(thatbeat, 0, NUM_LEDS);
  int pos = (pos1 + pos2) / 2;

  if (pos > (NUM_LEDS - 1))
    pos = 0;

  leds[pos] += ColorFromPalette(currentPalette, myhue++, thisbri, currentBlending);
}
