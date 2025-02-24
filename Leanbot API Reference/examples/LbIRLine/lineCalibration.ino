/*
  Steps to perform black/white sampling with tbX touch button:
 
  1. Initially, all 4 RGB LEDs blink red indicating Leanbot is not aligned
  2. Lift and place Leanbot so that all 4 IR Line sensors are looking at the white area
  3. Touch the tbX button (1st time) to read the white level value
  4. All 4 RGB Leds turn to flashing yellow, indicating that the white level alignment is complete
  5. Lift and place Leanbot so that all 4 IR line sensors look at the black area
  6. Touch the tbX button (2nd time) to read the black level value
  7. Leanbot goes into test mode:
     RGB led blinks green if sensor looks at black area
  8. (Optional) Lift Leanbot to different positions
     and observe 4 RGB leds to see if 4 sensors have correctly distinguished black/white
  9. After enough testing to see that 4 sensors have correctly distinguished black/white
     then touch the tbX button (3rd, last time) to finish the alignment
 
  If there is an error during alignment (wrong operation or RGB led is displayed incorrectly)
    Then press the Reset button to start over
*/

#include <Leanbot.h>

void setup() {
  Leanbot.begin();                          // initialize Leanbot
  LbIRLine.doManualCalibration(TB1A);       // use the TB1A button to align the black/white discrimination threshold value
}

void loop() {
  byte line = LbIRLine.read();              // Read the value of 4 bar sensors
  LbIRLine.displayOnRGB(line, CRGB::Blue);  // Display bar sensor status on RGB LED
  LbIRLine.println(line);                   // transfer the results to the computer

  delay(200);                               // time delay between each reading
}
