#ifndef NRF24L01_h
#define NRF24L01_h

#include "API.h"

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

//*********************************************
#define SPI_PORT PORTB
#define SPI_DIR  DDRB
#define SPI_IN   PINB
//---------------------------------------------
//---------------------------------------------
#define CE       0x01
// CE_BIT:   Digital Input     Chip Enable Activates RX or TX mode
#define SCK      0x04
// SCK BIT:  Digital Input     SPI Clock

#define MISO     0x10
// MISO BIT: Digital Output    SPI Slave Data Output, with tri-state option
#define CSN      0x02
// CSN BIT:  Digital Input     SPI Chip Select
#define MOSI     0x08
// MOSI BIT: Digital Input     SPI Slave Data Input
#define IRQ      0x20
// IRQ BIT:  Digital Output    Maskable interrupt pin
//*********************************************

unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = {0x34, 0x43, 0x10, 0x10, 0x01}; // Define a static TX address

//**************************************************
// Function: init_io();
// Description:
// flash led one time,chip enable(ready to TX or RX Mode),
// Spi disable,Spi clock line init high
//**************************************************
void init_io(void)
{
  SPI_PORT &= ~CE;    // chip enable
  SPI_PORT |= CSN;    // Spi disable
  SPI_PORT &= ~SCK;   // Spi clock line init high
}

/*
   Function: SPI_RW();

   Description:
   Writes one unsigned char to nRF24L01, and return the unsigned char read
   from nRF24L01 during write, according to SPI protocol
*/
unsigned char SPI_RW(unsigned char Byte)
{
  unsigned char i;
  for (i = 0; i < 8; i++){
    if (Byte & 0x80)
      SPI_PORT |= MOSI;   // output 'unsigned char', MSB to MOSI
    else
      SPI_PORT &= ~MOSI;
    SPI_PORT |= SCK;                    // Set SCK high..
    Byte <<= 1;                         // shift next bit into MSB..
    if (SPI_IN & MISO)
      Byte |= 1;                // capture current MISO bit
    SPI_PORT &= ~SCK;                   // ..then set SCK low again
  }
  return (Byte);                    // return read unsigned char
}

/*
   Function: SPI_RW_Reg();

   Description:
   Writes value 'value' to register 'reg'
*/
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
  unsigned char status;

  SPI_PORT &= ~CSN;                 // CSN low, init SPI transaction
  status = SPI_RW(reg);             // select register
  SPI_RW(value);                    // ..and write value to it..
  SPI_PORT |= CSN;                  // CSN high again

  return (status);                  // return nRF24L01 status unsigned char
}

/*
   Function: SPI_Read();

   Description:
   Read one unsigned char from nRF24L01 register, 'reg'
*/
unsigned char SPI_Read(unsigned char reg)
{
  unsigned char reg_val;

  SPI_PORT &= ~CSN;              // CSN low, initialize SPI communication...
  SPI_RW(reg);                   // Select register to read from..
  reg_val = SPI_RW(0);           // ..then read register value
  SPI_PORT |= CSN;               // CSN high, terminate SPI communication

  return (reg_val);              // return register value
}

/*
   Function: SPI_Read_Buf();

   Description:
   Reads 'unsigned chars' #of unsigned chars from register 'reg'
   Typically used to read RX payload, Rx/Tx address
*/
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
  unsigned char status, i;

  SPI_PORT &= ~CSN;                 // Set CSN low, init SPI tranaction
  status = SPI_RW(reg);             // Select register to write to and read status unsigned char

  for (i = 0; i < bytes; i++)
  {
    pBuf[i] = SPI_RW(0);    // Perform SPI_RW to read unsigned char from nRF24L01
  }

  SPI_PORT |= CSN;                 // Set CSN high again

  return (status);                 // return nRF24L01 status unsigned char
}

/*
   Function: SPI_Write_Buf();

   Description:
   Writes contents of buffer '*pBuf' to nRF24L01
   Typically used to write TX payload, Rx/Tx address
*/
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
  unsigned char status, i;

  SPI_PORT &= ~CSN;                 // Set CSN low, init SPI tranaction
  status = SPI_RW(reg);             // Select register to write to and read status unsigned char
  for (i = 0; i < bytes; i++)       // then write all unsigned char in buffer(*pBuf)
  {
    SPI_RW(*pBuf++);
  }
  SPI_PORT |= CSN;                 // Set CSN high again
  return (status);                 // return nRF24L01 status unsigned char
}

/*
   Function: RX_Mode();

   Description:
   This function initializes one nRF24L01 device to
   RX Mode, set RX address, writes RX payload width,
   select RF channel, datarate & LNA HCURR.
   After init, CE is toggled high, which means that
   this device is now ready to receive a datapacket.
*/
void RX_Mode(void)
{
  SPI_PORT &= ~CE;
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
  SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
  SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); // Select same RX payload width as TX Payload width
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:RX. RX_DR enabled..
  SPI_PORT |= CE;                           // Set CE pin high to enable RX device
  //  This device is now ready to receive one packet of 16 unsigned chars payload from a TX device sending to address
  //  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.
}

/*
   Function: TX_Mode();

   Description:
   This function initializes one nRF24L01 device to
   TX mode, set TX address, set RX address for auto.ack,
   fill TX payload, select RF channel, datarate & TX pwr.
   PWR_UP is set, CRC(2 unsigned chars) is enabled, & PRIM:TX.

   ToDo: One high pulse(>10us) on CE will now send this
   packet and expext an acknowledgment from the RX device.
*/
void TX_Mode(unsigned char * tx_buf)
{
  SPI_PORT &= ~CE;

  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // RX_Addr0 same as TX_Adr for Auto.Ack

  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
  SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
  SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
  SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:TX. MAX_RT & TX_DS enabled..
  SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);

  SPI_PORT |= CE;
}
#endif

