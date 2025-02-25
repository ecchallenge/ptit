//  Leanbot bắn tia laze khi nhấn nút `TB1A`.
#include <Leanbot.h>

class cLbLaze {
  public:
    void begin();
    void shoot();
};

void LbLaze::begin() {
  pinMode(13, OUTPUT);
}

void LbLaze::shoot() {
  Serial.println("shoot");
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(13, LOW);
}

cLbLaze LbLaze;

void setup() {
  Leanbot.begin();
  LbLaze.begin();
}

void loop() {
  if (LbTouch.read(TB1A)) {
    LbLaze.shoot();
  }
}
