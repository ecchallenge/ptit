#include <Leanbot.h>

// the setup function runs once when you press reset or power the board
void setup() {
  Leanbot.begin();                      // initialize Leanbot
  pinMode(LED_BUILTIN, OUTPUT);         // initialize digital pin LED_BUILTIN as an output
}

// the loop function runs over and over again forever
void loop() {
  byte value1A = LbTouch.read(TB1A);
  digitalWrite(LED_BUILTIN, value1A);   // turn the LED on (HIGH is the voltage level)
}
