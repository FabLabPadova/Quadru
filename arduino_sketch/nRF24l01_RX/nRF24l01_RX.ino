#include "NRF24L01.h"
#include "utility.h"
#define DIM_GROUP 3

unsigned char rx_buf[TX_PLOAD_WIDTH];

String rec = "";
bool end_str = false;

void setup(){
  SPI_DIR = ( CE + SCK + CSN + MOSI);
  SPI_DIR &=~ ( IRQ + MISO);
  //  attachInterrupt(1, _ISR, LOW); // interrupt enable
  Serial.begin(9600);
  init_io();                        // Initialize IO port
  unsigned char status = SPI_Read(STATUS);
  Serial.print("status = ");
  Serial.println(status,HEX);      // There is read the mode’s status register, the default value should be ‘E’  
  Serial.println("*****************RX_Mode start******************************");
  RX_Mode();                        // set RX mode
}
void loop(){
  unsigned char status = SPI_Read(STATUS);                         // read register STATUS's value
  if(status&RX_DR){                                                 // if receive data ready (TX_DS) interrupt
    SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);             // read playload to rx_buf
    SPI_RW_Reg(FLUSH_RX,0);            // clear RX_FIFO
    unsigned int i = 0;
    while (i < TX_PLOAD_WIDTH && !(end_str = rx_buf[i] == '!'))
      rec += (char)rx_buf[i++];
    if (end_str) {
      scan_str();
      rec = "";
      end_str = false;
    }//if
  }//if-status
  SPI_RW_Reg(WRITE_REG+STATUS,status);                             // clear RX_DR or TX_DS or MAX_RT interrupt flag
}

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
