#include <Leanbot.h>


void setup() {
  Leanbot.begin();                   // initialize Leanbot
}


void loop() {
  LbRGB[ledO] = CRGB::Red;           // red setting
  LbRGB.show();                      // LED shows up
  LbDelay(1000);                     // light time

  LbRGB[ledO] = CRGB::Black;         // black setting
  LbRGB.show();
  LbDelay(1000);                     // off time
}
