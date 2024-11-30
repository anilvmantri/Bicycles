#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS 600   // Set to 600 pixels
#define NUMWAVES 5      // Adjust for number of waves
#define WAIT 10         // Faster wave speed (reduce delay)
#define MAX  255        // Max brightness Range 0 .. 255

#define PIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN);

uint8_t CIEL8[] = {
    0,  0,  0,  0,  0,  0,  0,  1,
    1,  1,  2,  2,  3,  3,  4,  5,
    6,  7,  8, 10, 11, 13, 14, 16,
   18, 20, 22, 25, 27, 30, 33, 36,
   39, 43, 47, 50, 55, 59, 63, 68,
   73, 78, 83, 89, 95,101,107,114,
  120,127,135,142,150,158,167,175,
  184,193,203,213,223,233,244,255,
  255,244,233,223,213,203,193,184,
  175,167,158,150,142,135,127,120,
  114,107,101, 95, 89, 83, 78, 73,
   68, 63, 59, 55, 50, 47, 43, 39,
   36, 33, 30, 27, 25, 22, 20, 18,
   16, 14, 13, 11, 10,  8,  7,  6,
    5,  4,  3,  3,  2,  2,  1,  1,
    1,  0,  0,  0,  0,  0,  0,  0 };

typedef unsigned short tick_t;
tick_t _previousTick = millis();
tick_t currentTick;
int16_t _fade = 0;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();
//  strip.setBrightness(MAX);
}

void loop() {

  currentTick = millis();
  if ( currentTick - _previousTick >= WAIT )
  {
    _fade = (_fade + 1) % 128; // Cycle through the CIEL8 curve
    for (int i = 0; i < strip.numPixels(); i++) {
      // Calculate intensity for red and green with opposing transitions
      uint8_t redIntensity = CIEL8[(_fade + i * (128 * NUMWAVES / strip.numPixels())) % 128];
      uint8_t greenIntensity = CIEL8[(128 - _fade + i * (128 * NUMWAVES / strip.numPixels())) % 128];
      
      // Set pixel color
      strip.setPixelColor(i, strip.Color(redIntensity, greenIntensity, 0));
    }
    strip.show();

    _previousTick = currentTick;
  }
}