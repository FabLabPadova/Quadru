#include "NRF24L01.h"

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

unsigned char tx_buf[TX_PLOAD_WIDTH] = {0};
bool stringComplete = false;
unsigned int i = 0;

void setup() 
{
  SPI_DIR = ( CE + SCK + CSN + MOSI);
  SPI_DIR &=~ ( IRQ + MISO);
  //  attachInterrupt(1, _ISR, LOW);// interrupt enable
  Serial.begin(9600);
  init_io();                        // Initialize IO port
  unsigned char status=SPI_Read(STATUS);
  Serial.print("status = ");    
  Serial.println(status,HEX);     // There is read the mode’s status register, the default value should be ‘E’
  TX_Mode(tx_buf);                       // set TX mode
}
void loop() 
{
    if (stringComplete){
      unsigned char status = SPI_Read(STATUS);                   // read register STATUS's value
      if(status&TX_DS)                                           // if receive data ready (TX_DS) interrupt
      {
        SPI_RW_Reg(FLUSH_TX,0);                                  
        SPI_Write_Buf(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);       // write playload to TX_FIFO
      }
      if(status&MAX_RT)                                         // if receive data ready (MAX_RT) interrupt, this is retransmit than  SETUP_RETR                          
      {
        SPI_RW_Reg(FLUSH_TX,0);
        SPI_Write_Buf(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);      // disable standy-mode
      }
      SPI_RW_Reg(WRITE_REG+STATUS,status);                     // clear RX_DR or TX_DS or MAX_RT interrupt flag
      stringComplete = false;
      i = 0;
      memset(tx_buf, 0, TX_PLOAD_WIDTH);
    }//if-c
}

void serialEvent() {
  while (Serial.available()) {
    tx_buf[i] = (char)Serial.read();
    if ((stringComplete = (tx_buf[i] == '!' || i == TX_PLOAD_WIDTH-1)))
      break;
    i++;
  }//while
}//serialEvent
