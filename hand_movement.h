#ifndef HAND_MOVEMENT_H
#define HAND_MOVEMENT_H

#include <Servo.h>

extern Servo thumb, index, middle, ring, pinky, back0, back1, back2;
extern int thumb_pos, index_pos, middle_pos, ring_pos, pinky_pos;

void open_hand();
void close_hand();

#endif
