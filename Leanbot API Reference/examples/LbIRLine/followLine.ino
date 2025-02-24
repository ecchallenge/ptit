#include <Leanbot.h>

int SPEED_MAX = 1000;             // run at a maximum speed of 1000
int SPEED_4   = 0.8 * SPEED_MAX;  // run at 80% speed
int SPEED_3   = 0.6 * SPEED_MAX;  // run at 60% speed
int SPEED_2   = 0.4 * SPEED_MAX;  // run at 40% speed
int SPEED_1   = 0.2 * SPEED_MAX;  // run at 20% speed
int SPEED_0   = 0.0 * SPEED_MAX;  // stop

void setup() {
  Leanbot.begin();                // initialize Leanbot
}

void loop() {
  byte line = LbIRLine.read(50);  // Read the value of 4 bar sensors with a threshold of 50
  LbIRLine.println(line);         // transfer the results to the computer

  switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_3);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_3, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;


    case 0b1111:
      LbMotion.runLR(SPEED_0, SPEED_0);
      break;
  }
}
