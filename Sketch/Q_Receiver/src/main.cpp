#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RF24Fast.h>
#include <Quadru.h>
#include <Utility.h>

#define DIM_GROUP 3
#define PIN_DEBUG 4
#define START_ELEMENT_LEG 5

#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

bool stringComplete = false;
unsigned int ii = 0;

LiquidCrystal_I2C lcd(0x27, 16, 4);
RF24Fast radio;
String rec = "";
bool end_str = false;
Quadru* ql = new Quadru();

void scan_str();
Quadru_Part_type getTypeFromInt (int n);
void sendToSlave ();

void setup(){
  Serial.begin(9600);
  Wire.begin();
  lcd.begin();
  pinMode(PIN_DEBUG, INPUT_PULLUP);
  //Set slave number
  for (int i=0; i<NUMBER_LEG; i++)
      ql->leg[i].n_slave = i;
  lcd.setCursor(0,2);
  lcd.print("Quadru ");
  radio.init(0xABCDABCD71LL, 0x544d52687CLL, ROLE_TX);
  radio.setRole(ROLE_RX);
  delay(2000);
}//setup

void loop() {
  if (stringComplete){
    scan_str();
    stringComplete = false;
    rec = "";
    ii = 0;
  }//if-c
}//loop

//Scan rec string. Every 3 character function captures string and convert hex to dec.
void scan_str() {
  char group[DIM_GROUP];
  unsigned int cg = 0, nleg = 0;
  int count_part = 0;
  //Start from 5 because first three characters are timing.
  for (unsigned int i = START_ELEMENT_LEG; i < rec.length(); i++) {
    group[cg] = rec.charAt(i);
    if ((i - 1) % DIM_GROUP == 0) {
      ql->leg[nleg].leg_parts[count_part].type = getTypeFromInt(count_part);
      ql->leg[nleg].leg_parts[count_part].micro_s_angle = conv_hex_to_dec(group, DIM_GROUP);
      count_part = (count_part == 2) ? (0) : (count_part + 1);
      cg = 0;
      nleg += ((i - (START_ELEMENT_LEG-1)) % (DIM_GROUP * 3) == 0);
    }//if
    else
      cg++;
  }//for

  if (digitalRead(PIN_DEBUG)){
    printQuadruInfo(ql, lcd);
  }//if-debug
  sendToSlave();
}//scan_str

void sendToSlave (){
  for (unsigned int i=0; i<NUMBER_LEG; i++){
    Wire.beginTransmission(ql->leg[i].n_slave);
    for (unsigned int j=0; j<NUMBER_PART_LEG; j++){
      Wire.write((ql->leg[i].leg_parts[j].micro_s_angle) >> 8);
      Wire.write((ql->leg[i].leg_parts[j].micro_s_angle) & 255);
    }//for-j
    Wire.endTransmission();
  }//for-i
}//sendToSlave

Quadru_Part_type getTypeFromInt (int n){
  Quadru_Part_type tret = FOO;
  switch (n) {
    case (0):
      tret = FEMORE;
      break;
    case (1):
      tret = TIBIA;
      break;
    case (2):
      tret = ROTAZIONE;
      break;
    case (3):
      tret = FOO;
      break;
   }//switch
   return tret;
}//getTypeFromInt

void serialEvent() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    rec += c;
    if ((stringComplete = (c == '!'))){
      break;
    }
    ii++;
  }//while
}//serialEvent
