
#include <Leanbot.h>

void setup() {
  Leanbot.begin();
}

void loop() {
  LbGripper.close();
  delay(2000);

  LbGripper.open();
  delay(4000);
}
