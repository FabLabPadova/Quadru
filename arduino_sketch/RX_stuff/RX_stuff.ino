#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define PIPE 0xE8E8F0F0E1LL
#define BUFFER_SIZE 32
#define DIM_GROUP 3

RF24 radio(CE_PIN, CSN_PIN);
char stuff[BUFFER_SIZE]; 
bool full_string_complete = false;
String rec = "";
bool end_str = false;

int conv_hex_to_dec(const char * shex, const unsigned int len);
void scan_str();
int _pow (unsigned int base, unsigned int exponent);

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
      Serial.print(rec.charAt(0));
      Serial.print(rec.charAt(1));
      Serial.print(':');
      scan_str();
      rec = "";
      end_str = false;
    }//if
}//loop

//Scan rec string. Every 3 character function captures string and convert hex to dec.
void scan_str(){
  char group[DIM_GROUP];
  int m = 0;
  for (unsigned int i=2; i<rec.length(); i++){
    group[m] = rec.charAt(i);
    if ((i-1) % 3 == 0){
      Serial.print(conv_hex_to_dec(group, DIM_GROUP));
      Serial.print(' ');
      m = 0;
    }//if
    else
      m++;
  }//for
  Serial.println();
}//scan_str

/*
  IP: shex const char rappresentation of hexadecimal number in char array.
  IV: len int shex's length.
  OR: shex converted into integer number.
*/
int conv_hex_to_dec(const char * shex, const unsigned int len){
    unsigned int dec = 0;
    for (unsigned int i=0; i<len; i++)
      dec += (_pow(16, len-i-1)) * ( (shex[i] >= '0' && shex[i] <= '9')*(shex[i] - '0') + (shex[i] >= 'A' && shex[i] <= 'F') * (shex[i] - 'A' + 10) );
    return dec;
}//conv_hex_to_dec

//pow function for integer. So, the original one return result minus 1...?
int _pow (unsigned int base, unsigned int exponent){
  unsigned int ris = 1;
  for (unsigned int i=0; i<exponent; i++)
    ris *= base;
  return ris;
}

