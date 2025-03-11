#ifndef HAND_MOVEMENT_H
#define HAND_MOVEMENT_H

#include <Servo.h>

// MAKE SURE TO USE PWM PINS
#define SERVO_PIN_THUMB 13
#define SERVO_PIN_IND 12
#define SERVO_PIN_MIDDLE 11
#define SERVO_PIN_RING 10
#define SERVO_PIN_PINKY 9
#define SERVO_PIN_BACK0 8
#define SERVO_PIN_BACK1 7
#define SERVO_PIN_BACK2 6

extern Servo thumb, ind, middle, ring, pinky, back0, back1, back2;
extern int thumb_pos, ind_pos, middle_pos, ring_pos, pinky_pos;

void setup_hand();
void open_hand();
void close_hand();

#endif
