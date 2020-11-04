#include <Encoder.h> // include the encoder library

Encoder enc(14, 15); // create an encoder object

long current_value; // current read
long previous_value = -999; // previous read

void setup() {
  Serial.begin(57600); // open serial port
}

void loop() {
   
  current_value = enc.read(); // read the value of the encoder
  
  if (current_value != previous_value) { // compare to previous reading
    Serial.println(current_value); // if it's changed, print to serial port
    previous_value = current_value; // store the reading for next comparison
  }
}
