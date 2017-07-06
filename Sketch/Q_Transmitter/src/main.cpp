#include <Arduino.h>
#include <RF24Fast.h>

#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

String ssend = "";
bool stringComplete = false;
unsigned int i = 0;
RF24Fast radio;

void setup()
{
  radio.init(0xABCDABCD71LL, 0x544d52687CLL, ROLE_RX);
  radio.setRole(ROLE_TX);
  //  attachInterrupt(1, _ISR, LOW);// interrupt enable
  Serial.begin(9600);           // Initialize IO port
}

void loop()
{
    if (stringComplete){
      radio.writeString(ssend);
      stringComplete = false;
      ssend = "";
      i = 0;
    }//if-c
}

void serialEvent() {
  while (Serial.available()) {
    ssend[i] = (char)Serial.read();
    if ((stringComplete = (i == TX_PLOAD_WIDTH-1))){
      ssend[i-1] = ';';
      break;
    }
    i++;
  }//while
}//serialEvent
