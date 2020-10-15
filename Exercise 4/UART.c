#include <avr/io.h>
#include <stdio.h>
#include "UART.h"

#define BAUD 9600

// here we initialize the uart and set the baud rate
void UART_init(unsigned long extclock)
{	
	unsigned long baud=BAUD;		
	
	unsigned char ubbr = (extclock / (16 * baud))-1;	
	//set baud rate
	UBRR0H = ubbr>>8;
	UBRR0L = ubbr;
	
	//set frame format: 8 data, 1 stop bits
	UCSR0C |= (1<<URSEL0)|(1<<USBS0)| (3<<UCSZ00);
	
	//enable reciever and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	fdevopen(UART_Transmit , UART_Recieve);
	
}

uint8_t UART_Transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0))) ;
	UDR0 = data;	
	return 0;
}

uint8_t UART_Recieve(void)
{
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}







/*
static bool is_UARTdataempty(void)
{
return UCSR0A & (1 << UDRE0);	
}


*/