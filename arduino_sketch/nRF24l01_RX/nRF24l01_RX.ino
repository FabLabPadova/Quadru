#include <Wire.h>
#include <Servo.h>
#include "NRF24L01.h"
#include "Quadru.h"
#include "utility.h"

#define DIM_GROUP 3
#define PIN_DEBUG 4
#define START_ELEMENT_LEG 5

unsigned char rx_buf[TX_PLOAD_WIDTH];
String rec = "";
bool end_str = false;
Quadru* ql = new Quadru();

void setup(){
  Wire.begin();
  pinMode(PIN_DEBUG, INPUT_PULLUP);
  //Set slave number
  for (int i=0; i<NUMBER_LEG; i++)
    ql->leg[i].n_slave = i;
  SPI_DIR = (CE + SCK + CSN + MOSI);
  SPI_DIR &= ~ (IRQ + MISO);
  init_io();                        // Initialize IO port
  unsigned char status = SPI_Read(STATUS);
  Serial.begin(115200);
  Serial.print("status = ");
  Serial.println(status, HEX);     // There is read the mode’s status register, the default value should be ‘E’
  Serial.println("RX_Mode start...");
  RX_Mode();                        // set RX mode
}//setup

void loop() {
  unsigned char status = SPI_Read(STATUS);                         // read register STATUS's value
  if (status & RX_DR) {                                             // if receive data ready (TX_DS) interrupt
    SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);             // read playload to rx_buf
    SPI_RW_Reg(FLUSH_RX, 0);           // clear RX_FIFO
    unsigned int i = 0;
    while (i < TX_PLOAD_WIDTH && !(end_str = rx_buf[i] == '!'))
      rec += (char)rx_buf[i++];
    if (end_str) {
      scan_str();
      rec = "";
      end_str = false;
    }//if
  }//if-status
  SPI_RW_Reg(WRITE_REG + STATUS, status);                          // clear RX_DR or TX_DS or MAX_RT interrupt flag
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
  if (digitalRead(PIN_DEBUG))
    printQuadruInfo(ql);
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

