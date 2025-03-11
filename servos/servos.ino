#include <Servo.h>
#include "../hand_movement.h"

#define SERVO_PIN_THUMB 13
#define SERVO_PIN_INDEX 12
#define SERVO_PIN_MIDDLE 11
#define SERVO_PIN_RING 10
#define SERVO_PIN_PINKY 9
#define SERVO_PIN_BACK0 8
#define SERVO_PIN_BACK1 7
#define SERVO_PIN_BACK2 6

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;

Servo back0;
Servo back1;
Servo back2;

int thumb_pos, index_pos, middle_pos, ring_pos, pinky_pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  thumb.attach(SERVO_PIN_THUMB);
  index.attach(SERVO_PIN_INDEX);
  middle.attach(SERVO_PIN_MIDDLE);
  ring.attach(SERVO_PIN_RING);
  pinky.attach(SERVO_PIN_PINKY);
  back0.attach(SERVO_PIN_BACK0);
  back1.attach(SERVO_PIN_BACK1);
  back2.attach(SERVO_PIN_BACK2);

  Serial.println("starting");

  thumb_pos = 180;
  index_pos = 180;
  middle_pos = 0;
  ring_pos = 0;
  pinky_pos = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  open_hand();
  delay(2000);

  close_hand();
  delay(2000);
}
