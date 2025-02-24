
#include <Leanbot.h>

void setup() {
  // put your setup code here, to run once:
  Leanbot.begin();               // initialize Leanbot
  pinMode(LED_BUILTIN , OUTPUT);       // Configure the LED driver pin to be OUTPUT
}

void printButtons(int bits) {
  for (int i = 3; i >= 0; i--) {
    if (bitRead(bits, i)) {
      Serial.print(" #");
    } else {
      Serial.print(" .");
    }
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  LbDelay(100);

  byte touchBits = LbTouch.readBits();
  printButtons(touchBits);

  if (touchBits == 0b1111) {
    digitalWrite(LED_BUILTIN , HIGH);  // If all 4 buttons are touched then the light turns on
  } else {
    digitalWrite(LED_BUILTIN , LOW);   // If not, turn off the light
  }
}
