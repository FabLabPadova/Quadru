#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define LED_ON 7
#define LED_OFF 8
#define INTERVAL 5
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 32

RF24 radio(CE_PIN, CSN_PIN);

char stuff[BUFFER_SIZE];
bool stringComplete = false;
unsigned int i = 0;

inline void activityLed (const bool in_activity = true);

void serialEvent();

void setup(){
  Serial.begin(9600);
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_OFF, OUTPUT);
  digitalWrite(LED_OFF, HIGH);
  memset(stuff, 0, BUFFER_SIZE);
  radio.begin();
  radio.setChannel(125);
  radio.openWritingPipe(PIPE);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
}//setup

void loop(){
    if (stringComplete){
      activityLed();
      unsigned int c = 0;
      while (!radio.write(stuff, BUFFER_SIZE) && c < 2)
        c++;
      activityLed(false);
      stringComplete = false;
      i = 0;
      memset(stuff, 0, BUFFER_SIZE);
    }//if-string
}//loop

inline void activityLed (const bool in_activity){
  digitalWrite(LED_OFF, !in_activity);   
  digitalWrite(LED_ON, in_activity);
}//activityLed

void serialEvent() {
  while (Serial.available()) {
    stuff[i] = (char)Serial.read();
    if ((stringComplete = (stuff[i] == '!' || i == BUFFER_SIZE-1)))
      break;
    i++;
  }//while
}//serialEvent
