#include "HandControl.h"
#include <Arduino.h>

void open_hand() {
    thumb.write(180);
    index.write(180);
    middle.write(0);
    ring.write(0);
    pinky.write(0);
  
    back0.write(150);
    back1.write(90);
    back2.write(100);
  
    thumb_pos = 180;
    index_pos = 180;
    middle_pos = 0;
    ring_pos = 0;
    pinky_pos = 0;
    Serial.println("open");
  }

  void close_hand() {
    if (thumb_pos > 110)
      thumb.write(--thumb_pos);
    if (index_pos > 30)
      index.write(--index_pos);
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
  