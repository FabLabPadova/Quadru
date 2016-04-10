#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define LED_ON 7
#define LED_OFF 8
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 1

RF24 radio(CE_PIN, CSN_PIN);

char stuff[BUFFER_SIZE];
bool stringComplete = false;
unsigned int i = 0;

void serialEvent();

void setup(){
  Serial.begin(9600);
  memset(stuff, 0, BUFFER_SIZE);
  radio.begin();
  radio.setChannel(125);
  radio.openWritingPipe(PIPE);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
}//setup

void loop(){
  if (Serial.available()){
    char * stuff = new char((char)Serial.read());
    unsigned int c = 0;
    while (!radio.write(stuff, sizeof((*stuff))) && c < 2)
      c++;
    delete stuff;
    Serial.flush();
  }//if-available
}//loop
