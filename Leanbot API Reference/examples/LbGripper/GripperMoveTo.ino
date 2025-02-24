
#include <Leanbot.h>

void setup() {
  Leanbot.begin();
}

void loop() {
  LbGripper.moveTo(00);
  LbDelay(2000);

  LbGripper.moveTo(45);
  LbDelay(2000);

  LbGripper.moveTo(90);
  LbDelay(2000);

  LbGripper.moveTo(45);
  LbDelay(2000);
}
