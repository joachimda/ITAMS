/*
 * uartDriver.c
 * Created: 20-02-2017 13:04:32
 *  Author: Joachim
 */ 

#include <avr/io.h>
#include "uartDriver.h"
#include <stdlib.h>
#define  F_CPU 3686400
#include <util/delay.h>
#define  XTAL 3686400

void initializeUART(unsigned long baudRate, unsigned char dataBit)
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
unsigned char charReady()
{
   return UCSRA & (1<<7);
}


/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char readChar()
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
void sendChar(char Tegn)
{
	_delay_ms(50);
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSRA & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR = Tegn;

}

/*************************************************************************
Sends 0-terminated string.
Parameters:
string: Pointer to the string. 
*************************************************************************/
void sendString(char* s)
{
  // Repeat until zero-termination
  while (*s != 0)
  {
    // Send the character pointed to by "s"
    sendChar(*s);
    // Advance the pointer one step
    s++;
	_delay_ms(50);
  }
}

/*************************************************************************
Converts the integer "num" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameters:
num: The integer to be converted and send. 
*************************************************************************/
void SendInteger(int num)
{
char array[7];
  // Convert the integer till an ASCII string (array), radix = 10 
  itoa(num, array, 10);
  // - then send the string
  sendString(array);
}

/*************************************************************************
Flushed the RX buffer by toggling the receiver bit 4 in UCSRB
Parameters:
none
*************************************************************************/
void flushRxBuffer()
{
	UCSRB ^= (-0^UCSRB) & (1 << 4);
	UCSRB ^= (-1^UCSRB) & (1 << 4);
}

