# include <Servo.h>

# include "../hand_movement.h"
# include "../emg.h"

# define PRESSURE_ANALOG_PIN A1 // MUST BE AN ANALOG PIN

const int PRESSURE_DIFF_THRESHOLD = 100;

bool handClosed = false;

void setup() {
  Serial.begin(9600);

  pinMode(PRESSURE_ANALOG_PIN, INPUT);

  setup_hand();
  setup_emg();

  Serial.println("starting");
}

void loop() {
  bool close = readEMG();
  moveHand(close);
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
