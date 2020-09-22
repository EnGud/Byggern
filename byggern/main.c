/*
 * exercise 1.c
 *
 * Created: 27.08.2020 09:21:49
 * Author : harasa
 */ 
/*----------------------------------------------------------------------------------------------*/
//define the clock
#ifndef F_CPU
#define F_CPU 4915200UL
#endif
/*----------------------------------------------------------------------------------------------*/
/* include libraries */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

/* self made driver includes */
#include "UART.h"
#include "SRAM_DRIVER.h"
#include "ADC_driver.h"
// exercise 1
/*
int main(void)
{  
	
	UART_init(F_CPU);
	
    while (1) 
    {
	
		 
		printf(" $$$$$Dancing for gp$$$$$ \n join my youtube channel xxXB04sniperXxx_8==D first 10 get 1m ea ");
	
		_delay_ms(500);
    }
}
*/
/* exercise 2*//*
int main(void)
{	
	SRAM_INIT();
	UART_init(F_CPU);
	
	char data = 'd';
	char alpha;
	volatile char* ext_ram; 
	//= (char *) 0x1000;
	SRAM_Test();
	while(1)
	{
		
		//printf(" $$$$$Dancing for gp$$$$$ \n join my youtube channel xxXB04sniperXxx_8==D first 10 get 1m ea \r");
		ext_ram[0x1800] = data;
		//printf("OLED command\n");
		alpha= SRAM_READ(0x00);
		printf("%d",alpha);
		ext_ram[0x14FF] = data;//writing to the adc
		_delay_ms(300);
		//printf("OLED data\n");
		_delay_ms(300);
		ext_ram[0x400] = data;
		//printf("ADC\n");
		_delay_ms(3000);
		ext_ram[0x800] = data;
		//printf("SRAM\n");
		_delay_ms(3000);
	
		
		
		
		
		
	}
	
	
}
*/
//exercise 3
int main(void)
{
UART_init(F_CPU);
	char delta;
	while(1)
	{
DDRD|=(1<<DDD5);
PORTD|=(1<<PD5);
ADC_read(CHANNEL1);

//printf(" $$$$$Dancing for gp$$$$$ \n join my youtube channel xxXB04sniperXxx_8==D first 10 get 1m ea \r");

_delay_ms(100);


PORTD&=~(1<<PD5);
_delay_ms(100);
delta=(get_adcdata());
printf(delta);



	}
}