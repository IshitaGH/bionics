#include "emg.h"
#include <Arduino.h>

void setup_emg() {
    pinMode(EMG_PIN, INPUT);
}

// returns true if it detects muscle flexion, false otherwise
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
