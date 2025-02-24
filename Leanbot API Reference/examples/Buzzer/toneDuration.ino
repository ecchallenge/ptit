
#include <Leanbot.h>

void setup() {
  // put your setup code here, to run once:
  Leanbot.begin();                    // initialize Leanbot
}

void loop() {
  // put your main code here, to run repeatedly:
  Leanbot.tone(500, 1000);
  LbDelay(2000);
}
