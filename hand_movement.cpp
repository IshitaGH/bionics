#include "hand_movement.h"
#include <Arduino.h>

Servo thumb, ind, middle, ring, pinky, back0, back1, back2;

int thumb_pos, ind_pos, middle_pos, ring_pos, pinky_pos;

void setup_hand() {
    thumb.attach(SERVO_PIN_THUMB);
    ind.attach(SERVO_PIN_IND);
    middle.attach(SERVO_PIN_MIDDLE);
    ring.attach(SERVO_PIN_RING);
    pinky.attach(SERVO_PIN_PINKY);
    back0.attach(SERVO_PIN_BACK0);
    back1.attach(SERVO_PIN_BACK1);
    back2.attach(SERVO_PIN_BACK2);

    // Initialize positions to open hand
    thumb_pos = 180;
    ind_pos = 180;
    middle_pos = 0;
    ring_pos = 0;
    pinky_pos = 0;
}

void open_hand() {
    thumb.write(180);
    ind.write(180);
    middle.write(0);
    ring.write(0);
    pinky.write(0);
  
    back0.write(150);
    back1.write(90);
    back2.write(100);
  
    thumb_pos = 180;
    ind_pos = 180;
    middle_pos = 0;
    ring_pos = 0;
    pinky_pos = 0;
    Serial.println("open");
  }

  void close_hand() {
    if (thumb_pos > 110)
      thumb.write(--thumb_pos);
    if (ind_pos > 30)
      ind.write(--ind_pos);
    if (middle_pos < 110)
      middle.write(++middle_pos);
    if (ring_pos < 110)
      ring.write(++ring_pos);
    if (pinky_pos < 105)
      pinky.write(++pinky_pos);
  
    back0.write(90);
    back1.write(160);
    back2.write(160);
    Serial.println("close");
  }
