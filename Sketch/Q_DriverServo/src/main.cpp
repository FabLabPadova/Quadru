#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#define N_SLAVE 3

const int pin_servo[3] = {6,7,8};
Servo sevs[3];

void receiveEvent(int howMany);

void setup() {
  Wire.begin(N_SLAVE);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  for (int i=0; i<3; i++){
    sevs[i].attach(pin_servo[i]);
  }
}

void loop() {
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int n_pack = 0;
  while (1 < Wire.available() && n_pack < 3) { // loop through all but the last
    unsigned int n_rec = Wire.read() << 8;
    n_rec |= Wire.read();
    sevs[n_pack].writeMicroseconds(n_rec);
    n_pack++;
  }//while
}//receiveEvent
