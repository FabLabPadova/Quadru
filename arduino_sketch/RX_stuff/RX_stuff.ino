#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 32

RF24 radio(CE_PIN, CSN_PIN);
char stuff[BUFFER_SIZE]; 
bool full_string_complete = false;
String rec = "";
bool end_str = false;

const int conv_hex_to_dec(const char * shex, const int len);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,PIPE);
  radio.setChannel(125);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();
  memset(stuff, 0, BUFFER_SIZE);
}//setup

void loop(){
    if (radio.available()){
      bool done = false;
      while (!done)
        done = radio.read( stuff, BUFFER_SIZE );
      for (int i=0; i<BUFFER_SIZE; i++){
        if (stuff[i] == '!'){
          end_str = true;
          break;
        }//if
        rec += stuff[i];
      }//for
      memset(stuff, 0, BUFFER_SIZE);
    }//if-available
    if (end_str){
      Serial.println(rec);
      rec = "";
      end_str = false;
    }
}//loop

/*
  IP: shex const char rappresentation of hexadecimal number in char array.
  IV: len int shex's length.
  OR: shex converted into integer number.
*/
const int conv_hex_to_dec(const char * shex, const int len){
    int let_hex[6] = {10, 11, 12, 13, 14, 15};
    int dec = 0;
    for (int i=0; i<len; i++)
        dec+= (int)(pow(16, len-i-1)) * ((shex[i] >= '0' && shex[i] <= '9') * 
        (shex[i] - '0') + (shex[i] >= 'A' && shex[i] <= 'F') * (shex[i] - 'A' + 10));
    return dec;
}//conv_hex_to_dec

