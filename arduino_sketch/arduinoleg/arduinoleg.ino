#include <Servo.h>
#include <Wire.h>

#define N_SLAVE 2
#define N_PART 3
#define ANGLE_OPPOSITE 2
#define ORIGIN 1500

const int pin_servo[N_PART] = {3,5,6};
int receivedValue;
int servo_to_act = 0;
Servo motor_leg[N_PART];

void setup() {
  pinMode(ANGLE_OPPOSITE, INPUT_PULLUP);
  for (int i=0; i<N_PART; i++)
    motor_leg[i].attach(pin_servo[i]);
  Wire.begin(N_SLAVE);
  Wire.onReceive(receiveEvent);
}//setup

void loop() {}

void receiveEvent (int howMany){
  while (Wire.available()){
    int receivedValue = Wire.read() << 8;
    receivedValue |= Wire.read();
    if (servo_to_act != 2){
      if (digitalRead(ANGLE_OPPOSITE)){
        receivedValue = (ORIGIN * 2) - receivedValue;
        Serial.println("inverti");
      }
        
    }//if
    motor_leg[servo_to_act].writeMicroseconds(receivedValue);
    servo_to_act = (servo_to_act == N_PART-1) ? (0) : (servo_to_act+1);
  }//receiveEvent
}//receiveEvent

