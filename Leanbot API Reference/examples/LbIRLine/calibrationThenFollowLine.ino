#include <Leanbot.h>
 
int speed = 1000;                        // Speed of movement
 
void setup() {
  Leanbot.begin();                       // initialize Leanbot
  LbIRLine.doManualCalibration(TB1A);    // touch TB1A to measure black/white level, calibrate line sensors
//LbIRLine.setThreshold(300, 300, 300, 300);    // or measure first and then edit the threshold in the code
}
 
void loop() {
  LbMission.begin();                     // start mission
 
  // follow the black line while still seeing the black line
  do {
    followLineCarefully();
  } while ( LbIRLine.isBlackDetected() );
 
  LbMission.end();                       // stop, finish the mission
}
 
void followLineCarefully() {             // Follow the black line, if you don't see the black line, read it several more times to be sure
  for (int i = 0; i < 30; i++) {         // go up to 30*1mm = 30mm when the black line is not visible
    runFollowLine();
    if ( LbIRLine.isBlackDetected() ) {
      break;
    }
    LbMotion.waitDistanceMm(1);          // go 1mm and then read the sensor again
  }
}
 
void runFollowLine() {
  byte lineValue = LbIRLine.read();      // Read the value of 4 line sensors
  LbIRLine.displayOnRGB(CRGB::DarkCyan); // Display the result on RGB Leds for observation
 
  switch (lineValue) {                   // check the position of the black line relative to Leanbot
    case 0b0100:                         // .o.. - if the black line off to the left
    case 0b1110:                         // ooo.
      LbMotion.runLR(0, +speed);         //        turn left
      break;

    case 0b1100:                         // oo..
    case 0b1000:                         // o...
      LbMotion.runLR(-speed, +speed);    //        spin left
      break;

    case 0b0010:                         // ..o. - if the black line off to the right
    case 0b0111:                         // .ooo
      LbMotion.runLR(+speed, 0);         //        turn right
      break;

    case 0b0011:                         // ..oo
    case 0b0001:                         // ...o
      LbMotion.runLR(+speed, -speed);    //        spin right
      break;

    default:                             // all other cases
      LbMotion.runLR(+speed, +speed);    //        go straight
  }
}
