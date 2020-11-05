/*
 * SPI.c
 *
 * Created: 29.10.2020 10:24:19
 *  Author: harasa
 */

#include <avr/io.h>
#include <stdint.h>
#include "SPI.h" 
#define DDR_SPI DDRB //spi inerface
#define DD_SCK PB7 //SPI clock
#define DD_MISO PB6 //Miso pin
#define DD_MOSI PB5 //MOSI pin
#define SS_PIN PB4 //slave select pin.



void SPI_init(void){
	
	DDR_SPI |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<SS_PIN); //set mosi and sck as output all others as input	
	
	SPCR |=	(1<<SPE) | (1<<MSTR) | (1<<SPR0); // enable spi, master, clock rate f/16
		
}
void SPI_write(char c){
	
	SPDR = c;
	while(!(SPSR &(1<<SPIF)));
	
}
char SPI_read(){
	
	SPI_write(0);
	uint8_t temp = SPDR;
	return temp;
}

void SPI_SLAVE_EN(uint8_t enable)
{
	if(enable){
		PORTB &=~(1<<SS_PIN);
	}
	else if(!enable){
		PORTB |=(1<<SS_PIN);
		
	}
}