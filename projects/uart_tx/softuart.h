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
#ifndef PIN_UART_RX
  #define PIN_UART_RX 2
#endif
#ifndef GP_RX
  #define GP_RX _CONCAT(RA,PIN_UART_RX)
#endif

#ifndef PIN_UART_TX
  #define PIN_UART_TX 0
#endif
#ifndef GP_TX
  #define GP_TX _CONCAT(RA,PIN_UART_TX)
#endif

//Function Declarations
void          softuart_init(void);
unsigned char softuart_receive(void);
void          softuart_transmit(const unsigned char);
void          softuart_print(const unsigned char*);

#endif
