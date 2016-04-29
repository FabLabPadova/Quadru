#include <Servo.h>
#include "NRF24L01.h"
#include "utility.h"

#define DIM_GROUP 3
#define NUMBER_LEG 4
#define NUMBER_PART_LEG 3
#define NUMBER_SEL 4
#define PIN_SERVO 6

const int SEL_DEMUX[NUMBER_SEL] = {2,3,4,5};

enum Quadru_Part_type {FEMORE = 0, TIBIA = 1, ROTAZIONE = 2};

struct Quadru_Part_Leg{
  Quadru_Part_type type;
  unsigned int micro_s_angle;
  unsigned int * sel_combo;
  int offset_target;
};

struct Quadru_Leg{
  Quadru_Part_Leg leg_parts[NUMBER_PART_LEG];
};

struct Quadru{
  Quadru_Leg leg[NUMBER_LEG];
};

unsigned char rx_buf[TX_PLOAD_WIDTH];

String rec = "";
bool end_str = false;
Servo ser_mux;
Quadru* ql = new Quadru();

void setup(){
  ser_mux.attach(PIN_SERVO);
  //Set output demux selectors.
  for (unsigned int i=0; i<NUMBER_SEL; i++)
    pinMode(SEL_DEMUX[i], OUTPUT);
  unsigned n_motor = 0;
  //Initialize selectors for each parts.
  for (unsigned int i=0; i<NUMBER_LEG; i++)
    for (unsigned int j=0; j<NUMBER_PART_LEG; j++)
      ql->leg[i].leg_parts[j].sel_combo = conv_number_array_bin(n_motor++, NUMBER_SEL);
  SPI_DIR = (CE + SCK + CSN + MOSI);
  SPI_DIR &= ~ (IRQ + MISO);
  //  attachInterrupt(1, _ISR, LOW); // interrupt enable
  init_io();                        // Initialize IO port
  unsigned char status = SPI_Read(STATUS);
  Serial.begin(9600);
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
          ql->leg[nleg].leg_parts[0].type = FEMORE;
          break;
        case (1):
          ql->leg[nleg].leg_parts[1].type = TIBIA;
          break;
        case (2):
          ql->leg[nleg].leg_parts[2].type = ROTAZIONE;
          count_part = -1;
          break;
      }//switch
      ql->leg[nleg].leg_parts[indexOfPart].micro_s_angle = conv_hex_to_dec(group, DIM_GROUP);
      activeServo(ql->leg[nleg].leg_parts[indexOfPart].sel_combo, ql->leg[nleg].leg_parts[indexOfPart].micro_s_angle);
      cg = 0;
      nleg += ((i - 1) % (DIM_GROUP * 3) == 0);
    }//if
    else
      cg++;
  }//for
  //print_quadru_details(ql);
}//scan_str

void activeServo (const unsigned int * sel, unsigned int micro_s_angle){
  for (unsigned int i = 0; i<NUMBER_SEL; i++)
    digitalWrite(SEL_DEMUX[i], sel[i]);
  ser_mux.writeMicroseconds(micro_s_angle);
}//activeServo

void print_quadru_details(Quadru *qp) {
  for (int i = 0; i < NUMBER_LEG; i++) {
    Serial.print("Gamba : ");
    Serial.println(i);
    print_single_leg_part(qp->leg[i]);
    Serial.println("***");
  }//for
}//printQuadruDetails

void print_single_leg_part(Quadru_Leg lp){
  for (int i = 0; i < NUMBER_PART_LEG; i++){
    Serial.print("Part : ");
    String spart;
    switch (lp.leg_parts[i].type) {
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
    Serial.println(lp.leg_parts[i].micro_s_angle);
  }
}//printSingleLegPart

