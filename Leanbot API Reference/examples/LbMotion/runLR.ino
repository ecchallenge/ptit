#include <Leanbot.h>

void setup() {
  Leanbot.begin();                 // initialize Leanbot
}

void loop() {
  LbMotion.runLR(+400, +400);      // let Leanbot go straight
  LbDelay(3000);                   // keep running for 3 seconds

  LbMotion.runLR(-400, -400);      // give Leanbot back
  LbDelay(3000);                   // keep running for 3 seconds
}
