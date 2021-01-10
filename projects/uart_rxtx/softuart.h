// --------------------------------------------------------------------------
// Sample project uart_rxtx
//
// Software uart
// Source of uart-code:
// https://pic-microcontroller.com/pic12f675-software-uart-bit-banging-code-and-proteus-simulation/
//
// Author: M.Saeed Yasin
// https://saeedsolutions.blogspot.com
//
// Minor modifications for sdcc
// --------------------------------------------------------------------------

#include "picconfig.h"

#ifndef __SOFTUART_H
#define __SOFTUART_H

// baudrate should be B1200 or B2400
#define B1200
//#define B2400

#if defined B1200
  #define delay_bit()          delay_833()
  #define delay_bit_half()     delay_416()
#elif defined B2400
  #define delay_bit()          delay_416()
  #define delay_bit_half()     delay_208()
#endif

#define DataBitCount          8              // no parity, no flow control
#define UART_RX               GP2            // UART RX pin
#define UART_TX               GP0            // UART TX pin
#define UART_RX_DIR	      TRISIO2        // UART RX pin direction register
#define UART_TX_DIR	      TRISIO0        // UART TX pin direction register

//Function Declarations
void          softuart_init(void);
unsigned char softuart_receive(void);
void          softuart_transmit(const unsigned char);
void          softuart_print(const unsigned char*);

#endif
