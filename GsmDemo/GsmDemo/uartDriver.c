/*
 * uartDriver.c
 *
 * Created: 20-02-2017 13:04:32
 *  Author: Joachim
 */ 

#include <avr/io.h>
#include "uartDriver.h"
#include <stdlib.h>
#define  XTAL 3686400

void InitializeUART(unsigned long baudRate, unsigned char dataBit)
{
	unsigned int tempUBRR;
	 if ((baudRate >= 110) && (baudRate <= 115200) && (dataBit >=5) && (dataBit <= 8))
	 {
		 // "Normal" clock, no multiprocessor mode (= default)
		 UCSRA = 0b00100000;
		 // No interrupts enabled
		 // Receiver enabled
		 // Transmitter enabled
		 // No 9 bit operation
		 UCSRB = 0b00011000;
		 // Asynchronous operation, 1 stop bit, no parity
		 // Bit7 always has to be 1
		 // Bit 2 and bit 1 controls the number of data bits
		 UCSRC = 0b10000000 | (dataBit-5)<<1;
		 // Set Baud Rate according to the parameter BaudRate:
		 // Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
		 //                   then write the two 8-bit registers separately):
		 tempUBRR = XTAL/(16*baudRate) - 1;
		 // Write upper part of UBRR
		 UBRRH = tempUBRR >> 8;
		 // Write lower part of UBRR
		 UBRRL = tempUBRR;
	 }
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSRA & (1<<7);
}


/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
	// Wait for new character received
	while ( (UCSRA & (1<<7)) == 0 )
	{}
	// Then return it
	return UDR;
}

/*************************************************************************
Awaits transmitter-register ready.
Then it send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSRA & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR = Tegn;
}

/*************************************************************************
Sends 0-terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* s)
{
  // Repeat until zero-termination
  while (*s != 0)
  {
    // Send the character pointed to by "s"
    SendChar(*s);
    // Advance the pointer one step
    s++;
  }
}

/*************************************************************************
Converts the integer "num" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
      num: The integer to be converted and send. 
*************************************************************************/
void SendInteger(int num)
{
char array[7];
  // Convert the integer till an ASCII string (array), radix = 10 
  itoa(num, array, 10);
  // - then send the string
  SendString(array);
}

