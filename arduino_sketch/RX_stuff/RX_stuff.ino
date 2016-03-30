#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 50

RF24 radio(CE_PIN, CSN_PIN);
char stuff[BUFFER_SIZE]; 
int previousTime = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,PIPE);
  radio.startListening();
}//setup


void loop(){
    if (radio.available()){
      bool done = false;
      while (!done){
        done = radio.read( stuff, BUFFER_SIZE );
        for (int i=0; i<BUFFER_SIZE; i++)
          Serial.print(stuff[i]);
        Serial.println();
        memset(stuff, 0, BUFFER_SIZE);
      }//while
    }//if-available
}//loop

