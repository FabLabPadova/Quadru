#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define INTERVAL 10
#define LED_ACTIVITY 7
#define LED_OFF 8
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 50

RF24 radio(CE_PIN, CSN_PIN);

char stuff[BUFFER_SIZE];
int previousTime = 0;
int n_bytes = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LED_ACTIVITY, OUTPUT);
  pinMode(LED_OFF, OUTPUT);
  digitalWrite(LED_OFF, HIGH);
  memset(stuff, 0, BUFFER_SIZE);
  radio.begin();
  radio.openWritingPipe(PIPE);
  radio.printDetails();
}

void activityLed (bool in_activity = true);

void loop(){
  while (Serial.available())
    n_bytes = Serial.readBytesUntil('!', stuff, BUFFER_SIZE);
  int currentTime = millis();
  if ((currentTime - previousTime) >= INTERVAL){
    previousTime = currentTime;
    activityLed();
    if (n_bytes > 0){
      bool done = false;
      int c = 0;
      while (!done && c < 2){
        done = radio.write(stuff, BUFFER_SIZE);
        activityLed(false);
        c++;
      }//while
    }//if
    n_bytes = 0;
    memset(stuff, 0, BUFFER_SIZE);
  }//if
}//loop

void activityLed (bool in_activity){
  if (in_activity){
    digitalWrite(LED_OFF, LOW);
    digitalWrite(LED_ACTIVITY, HIGH);
  }else {
    digitalWrite(LED_OFF, HIGH);
    digitalWrite(LED_ACTIVITY, LOW);
  }//else
}//activityLed
