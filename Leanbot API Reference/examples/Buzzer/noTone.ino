
#include <Leanbot.h> 

void setup() {
  // put your setup code here, to run once:
  Leanbot.begin();                    // initialize Leanbot
}

void loop() {
  // put your main code here, to run repeatedly:
  Leanbot.tone(500);
  LbDelay(1000);
  Leanbot.noTone();
  LbDelay(1000);
}
