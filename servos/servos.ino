#include <Servo.h>
#define SERVO_PIN_0 13
#define SERVO_PIN_1 12
#define SERVO_PIN_2 11
#define SERVO_PIN_3 10
#define SERVO_PIN_4 9
#define SERVO_PIN_5 8
#define SERVO_PIN_6 7
#define SERVO_PIN_7 6

Servo thumb;
Servo index;
Servo middle;
Servo pinky;
Servo ring;

Servo back1;
Servo back2;
Servo back3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thumb.attach(SERVO_PIN_0);
  index.attach(SERVO_PIN_1);
  middle.attach(SERVO_PIN_2);
  ring.attach(SERVO_PIN_3);
  pinky.attach(SERVO_PIN_4);
  back1.attach(SERVO_PIN_5);
  back2.attach(SERVO_PIN_6);
  back3.attach(SERVO_PIN_7);
  Serial.println("starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  thumb.write(180);
  index.write(180);
  middle.write(0);
  ring.write(0);
  pinky.write(0);

  back1.write(90);
  back2.write(100);
  back3.write(150);
  Serial.println("open");
  delay(2000);

  thumb.write(110);
  index.write(30);
  middle.write(110);
  ring.write(110);
  pinky.write(105);

  back1.write(160);
  back2.write(160);
  back3.write(90);
  Serial.println("close");
  delay(2000);
}
