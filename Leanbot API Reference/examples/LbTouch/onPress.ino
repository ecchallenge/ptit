
#include <Leanbot.h>

void setup() {
  Leanbot.begin();               // initialize Leanbot
}

void loop() {
  if (LbTouch.onPress(TB1A)) {
    Serial.println("onPress TB1A");
  }

  if (LbTouch.onPress(TB1B)) {
    Serial.println("onPress  TB1B");
  }

  if (LbTouch.onPress(TB2A)) {
    Serial.println("onPress   TB2A");
  }

  if (LbTouch.onPress(TB2B)) {
    Serial.println("onPress    TB2B");
  }
}
