/*
 * ADC_driver.c
 *
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
volatile char ADCDATA;




void ADC_init(void)
{
	
	
	
	
} 
char get_adcdata(void)
{
	ADCDATA=ext_adc[0x00];
	return ADCDATA;
	
	
}

void ADC_read(channel_t channel)
{
	
	
	char data = 0x00;
	
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
	
	ext_adc[0x00] = data;
	
	
}

void adc_calibrate(void)
{
	
	
	
}
