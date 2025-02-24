#include <Leanbot.h>

void setup() {
  // put your setup code here, to run once:
  Leanbot.begin();                      // initialize Leanbot
}

void loop() {
  // put your main code here, to run repeatedly:
  int value1A = LbTouch.read(TB1A);
  int value1B = LbTouch.read(TB1B);
  int value2A = LbTouch.read(TB2A);
  int value2B = LbTouch.read(TB2B);

  if (value1A == HIGH) {  // Touch the TB1A button then turn left
    LbMotion.runLR(+500, +1000);
  }

  if (value1B == HIGH) {  // Touch the TB1B button then turn right
    LbMotion.runLR(+1000, +500);
  }

  if (value2A == HIGH) {  // Touch the TB2A button to move forward
    LbMotion.runLR(+1000, +1000);
  }

  if (value2B == HIGH) {  // Touch the TB2B button to stop
    LbMotion.stopAndWait();
  }
}
