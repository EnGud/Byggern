/*
 * ADC_driver.c
 *
 This code enables communication with the ADC by setting the correct registers and timers. It enables reading of the ADC.
 * Created: 17.09.2020 11:38:49
 *  Author: harasa
 */ 
#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC_driver.h"
#include "UART.h"
volatile char* ext_adc=0x1400;
volatile uint8_t ADCDATA;


//we need an interrupt to know when to read?
//we need a timer for the adc
void ADC_init(void)
{
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	DDRD|=(1<<PD5); //set pd5 as output
	 
	 cli();
	//enabling ext_addresses.
	//setting up the timer1 for clk/8
	TIMSK|=(1<<OCIE1A);
	//TIMSK|=(1<<TOIE1);
	//TCCR1A|= (1<<WGM10);
	OCR1AL = 1;
	TCCR1B |=(1<<WGM12)|(1<<CS10);
	//1,25 Mhz clock
	
	sei();
	
	return 0;
	
} 

ISR(TIMER1_COMPA_vect)
{
	PORTD^=(1<<PD5); //toggling pd5 every 1/125mhz second.
	
	
}

uint8_t get_adcdata(void)
{
	ADCDATA=ext_adc[0x00];
	//ext_adc[0x00]=0b00001000;
	return ADCDATA;
	
	
}

void ADC_read(channel_t channel)
{
	
	
	uint8_t data = 0x00;
	ext_adc[0x00]=0x00;
	
	switch (channel) {
		case CHANNEL1 :
		data = 0x01;
		break;
		case CHANNEL2 :
		data = 0x02;
		break;
		case CHANNEL3 :
		data = 0x03;
		break;
		case CHANNEL4 :
		data = 0x04;
		break;
		default:
		
		return EXIT_FAILURE;
	}
	
	
	
	ext_adc[0x00] = data|0b10000000;
	
	
}

