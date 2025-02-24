#include <Leanbot.h>


void setup() {
  Leanbot.begin();                    // initialize Leanbot
}

void loop() {
  unsigned int d = Leanbot.pingCm();  // Measure the distance to the obstacle in centimeters
  Serial.println(d);                  // Transfer the results to the computer
  delay(100);                         // Time delay between each measurement
}
