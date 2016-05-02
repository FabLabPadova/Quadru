#include <Servo.h>
#include <Wire.h>

#define N_SLAVE 0
#define N_PART 3

const int pin_servo[N_PART] = {3,5,6};
int rx_wire;
int servo_to_act = 0;
Servo motor_leg[N_PART];

void setup() {
  Serial.begin(9600);
  for (int i=0; i<N_PART; i++)
    motor_leg[i].attach(pin_servo[i]);
  Wire.begin(N_SLAVE);
  Wire.onReceive(receiveEvent);
}//setup

void loop() {}

void receiveEvent (int howMany){
  while (Wire.available()){
    rx_wire = Wire.read() << 8;
    Serial.println(rx_wire);
    motor_leg[servo_to_act].writeMicroseconds(rx_wire);
    servo_to_act = (servo_to_act == N_PART-1) ? (0) : (servo_to_act+1);
  }//receiveEvent
}//receiveEvent

