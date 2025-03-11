# include <Servo.h>

#include "../hand_movement.h"

#define SERVO_PIN_THUMB 13 // MUST BE A PWM PIN
#define SERVO_PIN_INDEX 12
#define SERVO_PIN_MIDDLE 11
#define SERVO_PIN_RING 10
#define SERVO_PIN_PINKY 9
#define SERVO_PIN_BACK0 8
#define SERVO_PIN_BACK1 7
#define SERVO_PIN_BACK2 6

# define EMG_PIN A0 // MUST BE AN ANALOG PIN
# define PRESSURE_ANALOG_PIN A1 // MUST BE AN ANALOG PIN

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;

Servo back0;
Servo back1;
Servo back2;

int thumb_pos, index_pos, middle_pos, ring_pos, pinky_pos;

const int EMG_THRESHOLD = 970;
const int PRESSURE_DIFF_THRESHOLD = 100;

bool handClosed = false;

void setup() {
  Serial.begin(9600);

  pinMode(EMG_PIN, INPUT);

  pinMode(PRESSURE_ANALOG_PIN, INPUT);

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
  bool close = readEMG();
  moveHand(close);
}

bool readEMG() {
  double sensorValue = analogRead(EMG_PIN);

  // divided by 1023 because arduino has a 10-bit resolution
  // multiplied by 5 because supplying 5V to the sensor from the arduino
  double millivolt = (sensorValue/1023)*5;

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Voltage: ");
  Serial.print(millivolt*1000);
  Serial.println(" mV");

  if(sensorValue > EMG_THRESHOLD)
    return true;
  else
    return false;
}

int readPressure() {
  int pressureReading = analogRead(PRESSURE_ANALOG_PIN);
  
  Serial.print("Pressure Pad Reading = ");
  Serial.println(pressureReading);

  return pressureReading;
}

// takes a rolling avg of the last 9 pressure readings and compares it to the current
// if the difference in the pressure readings is greater than the pressure threshold,
// keep closing the hand
// else, stop closing the hand because you are starting to crush the object
void closeHand() {
  const int NUM_READINGS = 10;
  int pressureReadings[NUM_READINGS] = {};
  int index = 0;
  int pressureTotal = 0
  while (!handClosed) {
    pressureTotal -= pressureReadings[index];
    double pressureAvg = double(pressureTotal) / (NUM_READINGS - 1);
    pressureReadings[index] = readPressure();

    if (abs(pressureReadings[index] - pressureAvg) > PRESSURE_DIFF_THRESHOLD) {
      close_hand();
    }
    else {
      handClosed = true;
    }

    pressureTotal += pressureReadings[index];
    index = (index + 1) % NUM_READINGS;
  }
}

void moveHand(bool close) {
  if (!close) {
    open_hand();
    return;
  }
  if (handClosed) {
    return;
  }
  closeHand();
}
