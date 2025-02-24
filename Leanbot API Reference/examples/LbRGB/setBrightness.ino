#include <Leanbot.h>


void setup() {
  Leanbot.begin();                    // initialize Leanbot
  LbRGB.fillColor(CRGB::White);
}


void loop() {
  for (int i = 0; i < 50; i++) {
    LbRGB.setBrightness(i);           // brightness setting
    LbRGB.show();                     // LED shows up
    LbDelay(25);                      // time delay between update
  }

  for (int i = 50; i > 0; i--) {
    LbRGB.setBrightness(i);
    LbRGB.show();
    LbDelay(25);
  }
}
