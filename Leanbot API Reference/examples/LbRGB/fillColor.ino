#include <Leanbot.h>

byte LbSmiley     = BITMAP(ledA, ledB, ledC, ledD);
byte LbFrowning   = BITMAP(ledA, ledF, ledE, ledD);
byte LbLeftArrow  = BITMAP(ledA, ledO, ledE, ledD, ledC);
byte LbRightArrow = BITMAP(ledD, ledO, ledF, ledA, ledB);


void setup() {
  Leanbot.begin();    // initialize Leanbot
}


void loop() {
  LbRGB.clear();
  LbRGB.fillColor(CRGB::Yellow, LbFrowning);
  LbRGB.show();
  LbDelay(2000);

  LbRGB.clear();
  LbRGB.fillColor(CRGB::Green, LbSmiley);
  LbRGB.show();
  LbDelay(2000);

  LbRGB.clear();
  LbRGB.fillColor(CRGB::Red, LbLeftArrow);
  LbRGB.show();
  LbDelay(2000);

  LbRGB.clear();
  LbRGB.fillColor(CRGB::Green, LbRightArrow);
  LbRGB.show();
  LbDelay(2000);
}
