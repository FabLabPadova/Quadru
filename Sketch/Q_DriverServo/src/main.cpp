#define I2C_SLAVE_ADDRESS 0x01
#include <TinyWireS.h>
#include <Arduino.h>
#include <SoftwareServo.h>
#define DELAY_SERVO 2.5

uint16_t reg_position;
SoftwareServo servo1;
byte time_received = 0;
uint64_t timer1 = 0;

void receiveEvent(uint8_t howMany);

void setup()
{
  digitalWrite(3, LOW); // Note that this makes the led turn on, it's wire this way to allow for the voltage sensing above.
  servo1.attach(1);
  servo1.writeMicroseconds(1500);
  servo1.refresh();
  delay(2000);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  timer1 = millis();
}

void loop()
{
  if (millis() - timer1 > DELAY_SERVO ){
    servo1.refresh();
    timer1 = millis();
  }//if-timer
  TinyWireS_stop_check();
}

/**
* The I2C data received -handler
*
* This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
* so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
*/
void receiveEvent(uint8_t howMany){
  if (time_received == 0){
    reg_position = TinyWireS.receive() << 8;
    time_received++;
  }
  else{
    reg_position |= TinyWireS.receive();
    servo1.writeMicroseconds(reg_position);
    servo1.refresh();
    time_received = 0;
  }

}
