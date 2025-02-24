#include <Leanbot.h>

void setup() {
  Leanbot.begin();                  // initialize Leanbot
}

void loop() {
  LbMotion.runLR(+400, +400);       // let Leanbot go straight
  LbMotion.waitDistance(4000);      // wait for Leanbot to reach 4,000 steps
  LbMotion.stopAndWait();           // let Leanbot stop slowly

  LbDelay(3000);                    // delay 3s


  LbMotion.runLR(-400, -400);       // let Leanbot go backwards
  LbMotion.waitDistance(4000);      // wait for Leanbot back 4,000 steps
  LbMotion.stopAndWait();

  LbDelay(3000);
}
