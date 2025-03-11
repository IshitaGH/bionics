#include <Servo.h>
#include "../hand_movement.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setup_hand();

  Serial.println("starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  open_hand();
  delay(2000);

  close_hand();
  delay(2000);
}
