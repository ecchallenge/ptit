#include <Leanbot.h>

void setup() {
  Leanbot.begin();                  // initialize Leanbot
}

void loop() {
  LbMotion.runLR(+400, +400);       // let Leanbot go straight
  LbMotion.waitDistanceMm(+100);    // wait for Leanbot to reach 100 mm = 10 cm
  LbMotion.stopAndWait();           // let Leanbot stop slowly

  LbDelay(3000);                    // delay 3s


  LbMotion.runLR(-400, -400);       // let Leanbot go backwards
  LbMotion.waitDistanceMm(-100);    // wait for Leanbot back 100 mm = 10 cm (negative number)
  LbMotion.stopAndWait();

  LbDelay(3000);
}
