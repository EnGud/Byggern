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
#include "joystickdriver.h"
#include "Oled.h"
#include <stdbool.h>
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
/*
int main(void)
{
UART_init(F_CPU);
ADC_init();

joystick_init();
joystick_calibrate();

joystickposition joy_pos;
//slider_position slider_pos;
	while(1)
	{

joy_pos=joystickgetpos();
printf("x position is %d, and y position is %d and slider is %p \r \n",joy_pos.x, joy_pos.y, joy_pos.direction);


//slider_pos =Joystick_getSliderPosition();
//printf("sliderr is %d, slidery is %d", slider_pos.left,slider_pos.right);

//delta=joystick_button(vbutton);

//printf(" $$$$$Dancing for gp$$$$$ \n join my youtube channel xxXB04sniperXxx_8==D first 10 get 1m ea \r");
//printf(" and the button value is %d ch1 \r \n",delta);
//channel 2 right slider, channel 3 left slider, channel 1 y, channel 4 x 

	}
}
*/
//exercise 4
int main(void)
{	
	UART_init(F_CPU);

	
	//ADC_init();

	
	ADC_init();
	oled_init();
	joystick_init();
	joystick_calibrate();

	/*joystickposition joy_pos;
	oled_reset();
	oled_pos(0,1);
	oled_print("harald's");
	oled_pos(1,1);
	oled_print("&&moneyguild&&");
	
	oled_pos(3,1);
	oled_print("apply todai");
	oled_pos(5,1);
	oled_print("for free CBT");
	bool delta= ((PINB & (1<<PINB1))); 
	while (delta==0)
	{	
		delta= ((PINB & (1<<PINB1))); 
		joy_pos=joystickgetpos();
		printf("x position is %d, and y position is %d and slider is %p \r \n",joy_pos.x, joy_pos.y, joy_pos.direction);
		
		if(joy_pos.x>90)
		{
			oled_reset();
			oled_pos(2,1);
			oled_print("you won 3");
			oled_pos(3,1);
			oled_print("free CBT");
			
		}
		
	
		
	//printf("doubling money in wildy bring bank");
	}
	*/
	while(1){
		
		
		
		
		
	}
		
}