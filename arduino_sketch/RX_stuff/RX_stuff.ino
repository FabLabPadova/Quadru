#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "utility.h"

#define CE_PIN   9
#define CSN_PIN 10
#define LED_ON 7
#define LED_ALERT 4
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 32
#define DIM_GROUP 3

char stuff[BUFFER_SIZE];
bool full_string_complete = false, end_str = false;
int current_line = 0, previous_line = 4, timeFailure = 0;
String rec = "";
RF24 radio(CE_PIN, CSN_PIN);

void activityLed (bool in_activity = true);
void scan_str();

void setup() {
  Serial.begin(9600);
  pinMode(LED_ALERT, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, PIPE);
  radio.setChannel(125);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();
}//setup

void loop() {
  if (radio.available()) {
    char * stuff = new char();
    while (!radio.read( stuff, sizeof(*stuff))){}//wait transmission done and receive data.
    Serial.print(*stuff);
    if (!(end_str = (*stuff) == '!'))
      rec += (*stuff);
    delete stuff;
  }//if-available
  if (end_str) {
    current_line = rec.charAt(0) - '0';
    digitalWrite(LED_ALERT, !((current_line == 0 && previous_line == 4) || (current_line == previous_line+1))); //are you sure to be brave enough? :)
    previous_line = current_line;
    scan_str();
    rec = "";
    end_str = false;
  }//if
}//loop

//Scan rec string. Every 3 character function captures string and convert hex to dec.
void scan_str() {
  char group[DIM_GROUP];
  unsigned int m = 0;
  for (unsigned int i = 2; i < rec.length(); i++) {
    group[m] = rec.charAt(i);
    if ((i - 1) % DIM_GROUP == 0) {
      Serial.print(conv_hex_to_dec(group, DIM_GROUP));
      Serial.print(' ');
      m = 0;
    }//if
    else
      m++;
  }//for
  Serial.println();
}//scan_str
