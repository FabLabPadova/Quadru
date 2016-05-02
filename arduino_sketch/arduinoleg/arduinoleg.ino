#include <Wire.h>
#define N_SLAVE 0
int rx_wire;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
}

void loop() {}

void receiveEvent (int howMany){
  while (Wire.available()){
    rx_wire = Wire.read() << 8;
    Serial.println(rx_wire);
  }
}//receiveEvent

