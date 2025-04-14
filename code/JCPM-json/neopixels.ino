#include <Adafruit_NeoPixel.h>

#define PIN 5  // NeoPixel data pin
#define NUMPIXELS 11  // Total number of NeoPixel LEDs
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setupNeoPixels() {
  pixels.begin();
  resetAllPixels();  // Set all pixels to off initially
}

void setPixelColor(int pixel, int r, int g, int b) {
  if (pixel >= 0 && pixel < pixels.numPixels()) {
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    pixels.show();  // Update to show the change
  }
}

void resetAllPixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    setPixelColor(i, 0, 0, 0);  // Turn off all LEDs
  }
}
