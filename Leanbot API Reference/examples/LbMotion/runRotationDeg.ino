#include <Leanbot.h>

void setup() {
  Leanbot.begin();                                 // initialize Leanbot
}

void loop() {
  int speed = 1000;                                // speed of movement

  // Rotate from left to right 4 times:
  for (int i = 0; i < 4; i++) {
    LbMotion.runRotationDeg(+speed, -speed, +90);  // rotates approximately 90 degrees
    LbDelay(2000);                                 // delay 2s
  }

  // Rotate from right to left 4 times:
  for (int i = 0; i < 4; i++) {
    LbMotion.runRotationDeg(-speed, +speed, -90);  // rotates approximately 90 degrees
    LbDelay(2000);
  }
}
