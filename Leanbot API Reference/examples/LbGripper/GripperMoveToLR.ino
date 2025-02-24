
#include <Leanbot.h>

void setup() {
  Leanbot.begin();
}

void loop() {
  LbGripper.moveToLR(30, 60, 1500);
  LbDelay(2000);

  LbGripper.moveToLR(90, 90, 1000);
  LbDelay(2000);

  LbGripper.moveToLR(00, 00, 4000);
  LbDelay(2000);
}
