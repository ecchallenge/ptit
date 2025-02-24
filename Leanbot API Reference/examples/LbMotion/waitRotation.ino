#include <Leanbot.h>

void setup() {
  Leanbot.begin();                        // initialize Leanbot
}

void loop() {
  int speed = 1000;                       // Speed of movement

  // the number of steps for Leanbot to turn an angle of approximately 90 degrees
  // need to change with each Leanbot, running speed, working surface
  int rotation90 = 1600;

  // Rotate from left to right 4 times, approximately 90 degrees each time:
  for (int i = 0; i < 4; i++) {
    LbMotion.runLR(+speed, -speed);       // let Leanbot turn right
    LbMotion.waitRotation(+rotation90);   // wait for full 1600 steps
    LbMotion.stopAndWait();               // let Leanbot stop slowly
    
    LbDelay(2000);                        // delay 2s
  }

  // Rotate from right to left 4 times, approximately 90 degrees each time:
  for (int i = 0; i < 4; i++) {
    LbMotion.runLR(-speed, +speed);       // let Leanbot turn left
    LbMotion.waitRotation(-rotation90);   // wait for full 1600 steps
    LbMotion.stopAndWait();

    LbDelay(2000);
  }
}
