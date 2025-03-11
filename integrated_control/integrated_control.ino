# include <Servo.h>

# define EMG_PIN A0 // MUST BE AN ANALOG PIN
# define SERVO_PIN 9 // MUST BE A PWM PIN
# define PRESSURE_ANALOG_PIN A1 // MUST BE AN ANALOG PIN

const int EMG_THRESHOLD = 970;
const int PRESSURE_DIFF_THRESHOLD = 100;

bool handClosed = false;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(EMG_PIN, INPUT);
  pinMode(PRESSURE_ANALOG_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  Serial.println("starting");
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
  int position = 0;
  int pressureTotal = 0
  while (!handClosed) {
    pressureTotal -= pressureReadings[index];
    double pressureAvg = double(pressureTotal) / (NUM_READINGS - 1);
    pressureReadings[index] = readPressure();

    if (abs(pressureReadings[index] - pressureAvg) > PRESSURE_DIFF_THRESHOLD) {
      myServo.write(position);
    }
    else {
      handClosed = true;
    }

    index = (index + 1) % NUM_READINGS;
    position++;
    pressureTotal += pressureReadings[index];
  }
}

void moveHand(bool close) {
  if (!close) {
    myServo.write(0);
    return;
  }
  if (handClosed) {
    return;
  }
  closeHand();
}