#include <Leanbot.h>

void setup() {
  Leanbot.begin();                 // initialize Leanbot
}

void loop() {
  byte line = LbIRLine.read(50);   // Read the value of 4 bar sensors with a threshold of 50
  LbIRLine.println(line);          // transfer the results to the computer
  delay(200);                      // time delay between each reading
}
