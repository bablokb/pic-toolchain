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

#include <stdint.h> 
#include "delay.h"
#include "softuart.h"

// --------------------------------------------------------------------------

void softuart_init(void)	{
  bitset(TRISA,PIN_UART_RX);      // input
  bitclear(TRISA,PIN_UART_TX);    // output
  GP_TX = 1;                      // TX pin is high in idle state
}

// --------------------------------------------------------------------------
unsigned char softuart_receive(void) {
  unsigned char DataValue = 0;

  //wait for start bit
  while(GP_RX==1);

  delay_bit();                 // one bit delay
  delay_bit_half();            // Take sample value in the mid of bit duration

  for ( unsigned char i = 0; i < DataBitCount; i++ ) {
    if ( GP_RX == 1 ) {  //if received bit is high
      DataValue += (1<<i);
    }
    delay_bit();
  }

  // Check for stop bit
  if ( GP_RX == 1 ) {       //Stop bit should be high
    delay_bit_half();
    return DataValue;
  } else {                    //some error occurred !
    delay_bit_half();
    return 0x000;
  }
}

// --------------------------------------------------------------------------

void softuart_transmit(const unsigned char DataValue) {
  /* Basic Logic
	   
     TX pin is usually high. A high to low bit is the starting bit and 
     a low to high bit is the ending bit. No parity bit. No flow control.
     BitCount is the number of bits to transmit. Data is transmitted LSB first.
     
  */

  // Send Start Bit
  GP_TX = 0;
  delay_bit();

  for ( unsigned char i = 0; i < DataBitCount; i++ ) {
    //Set Data pin according to the DataValue
    if( ((DataValue>>i)&0x1) == 0x1 ) {   //if Bit is high
      GP_TX = 1;
    } else {     //if Bit is low
      GP_TX = 0;
    }

    delay_bit();
  }

  //Send Stop Bit
  GP_TX = 1;
  delay_bit();
}

// --------------------------------------------------------------------------

void softuart_print(const unsigned char* string) {
  for (unsigned char *p = string; *p; p++) {
    softuart_transmit(*p);
  }
}
