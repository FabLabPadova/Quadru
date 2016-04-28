#include "NRF24L01.h"
#include "utility.h"
#define DIM_GROUP 3
#define NUMBER_LEG 4
#define NUMBER_PART_LEG 3

enum Quadru_Part {FEMORE = 0, TIBIA = 1, ROTAZIONE = 2};


struct Leg_part {
  Quadru_Part part[NUMBER_PART_LEG];
  unsigned int micro_s_angle[NUMBER_PART_LEG];
};

struct Quadru {
  Leg_part leg[NUMBER_LEG];
};

unsigned char rx_buf[TX_PLOAD_WIDTH];

String rec = "";
bool end_str = false;
Quadru* ql = new Quadru();

void setup() {
  SPI_DIR = ( CE + SCK + CSN + MOSI);
  SPI_DIR &= ~ ( IRQ + MISO);
  //  attachInterrupt(1, _ISR, LOW); // interrupt enable
  Serial.begin(9600);
  init_io();                        // Initialize IO port
  unsigned char status = SPI_Read(STATUS);
  Serial.print("status = ");
  Serial.println(status, HEX);     // There is read the mode’s status register, the default value should be ‘E’
  Serial.println("RX_Mode start...");
  RX_Mode();                        // set RX mode
}
void loop() {
  unsigned char status = SPI_Read(STATUS);                         // read register STATUS's value
  if (status & RX_DR) {                                             // if receive data ready (TX_DS) interrupt
    SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);             // read playload to rx_buf
    SPI_RW_Reg(FLUSH_RX, 0);           // clear RX_FIFO
    unsigned int i = 0;
    while (i < TX_PLOAD_WIDTH && !(end_str = rx_buf[i] == '!'))
      rec += (char)rx_buf[i++];
    if (end_str) {
      //Serial.println(rec);
      scan_str();
      rec = "";
      end_str = false;
    }//if
  }//if-status
  SPI_RW_Reg(WRITE_REG + STATUS, status);                          // clear RX_DR or TX_DS or MAX_RT interrupt flag
}

//Scan rec string. Every 3 character function captures string and convert hex to dec.
void scan_str() {
  char group[DIM_GROUP];
  unsigned int cg = 0, nleg = 0;
  int count_part = -1;
  for (unsigned int i = 2; i < rec.length(); i++) {
    group[cg] = rec.charAt(i);
    if ((i - 1) % DIM_GROUP == 0) {
      count_part++;
      unsigned int indexOfPart = count_part;
      switch (count_part) {
        case (0):
          ql->leg[nleg].part[0] = FEMORE;
          break;
        case (1):
          ql->leg[nleg].part[1] = TIBIA;
          break;
        case (2):
          ql->leg[nleg].part[2] = ROTAZIONE;
          count_part = -1;
          break;
      }//switch
      ql->leg[nleg].micro_s_angle[indexOfPart] = conv_hex_to_dec(group, DIM_GROUP);
      cg = 0;
      nleg += ((i - 1) % (DIM_GROUP * 3) == 0);
    }//if
    else
      cg++;
  }//for
  //printQuadruDetails(ql);
}//scan_str

void printQuadruDetails(Quadru *qp) {
  for (int i = 0; i < NUMBER_LEG; i++) {
    Serial.print("Gamba : ");
    Serial.println(i);
    printSingleLegPart(qp->leg[i]);
    Serial.println("***");
  }//for
}//printQuadruDetails

void printSingleLegPart(Leg_part lp) {
  for (int i = 0; i < NUMBER_PART_LEG; i++) {
    Serial.print("Part : ");
    String spart;
    switch (lp.part[i]) {
      case (FEMORE):
        spart = "femore ";
        break;
      case (TIBIA):
        spart = "tibia ";
        break;
      case (ROTAZIONE):
        spart = "rotazione ";
        break;
    }//switch
    Serial.println(spart);
    Serial.print("Microseconds Angle : ");
    Serial.println(lp.micro_s_angle[i]);
  }
}//printSingleLegPart

