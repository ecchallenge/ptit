//  Leanbot bắn tia laze khi nhấn nút `TB1A`.
#include <Leanbot.h>

#define LAZE 13

void LbLaze.Shoot(){
  Serial.println("shoot");
  digitalWrite(LAZE, HIGH);
  delay(2000);
  digitalWrite(LAZE, LOW);
}

void setup() {
    Leanbot.begin();
    pinMode(LAZE, OUTPUT);
}

void loop() {
    if (LbTouch.read(TB1A)) {
        LbLaze.Shoot();
    }
}
