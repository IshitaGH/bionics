# include <Servo.h>

# include "../hand_movement.h"
# include "../emg.h"

void setup() {
    Serial.begin(9600);
  
    pinMode(PRESSURE_ANALOG_PIN, INPUT);

    setup_hand();
    setup_emg();
  
    Serial.println("starting");
  }

void loop() {
    if (!readEMG()) {
        open_hand();
    }
    else {
        close_hand();
    }
}
  