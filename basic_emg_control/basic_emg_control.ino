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

const int EMG_THRESHOLD = 970; // adjust this based on the person

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
    if (!readEMG()) {
        open_hand();
    }
    else {
        close_hand();
    }
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
  