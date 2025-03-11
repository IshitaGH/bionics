#ifndef EMG_H
#define EMG_H

# define EMG_PIN A0 // MUST BE AN ANALOG PIN

const int EMG_THRESHOLD = 970; // adjust this based on the person

void setup_emg();
void read_emg();

#endif
