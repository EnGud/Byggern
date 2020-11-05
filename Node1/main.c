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
#include "menu.h"
#include "MCP2515.h"
#include "SPI.h"
#include "CAN.h"
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
	//UART_init(F_CPU);

	
	//ADC_init();

	
	//ADC_init();
	//oled_init();
	//joystick_init();
	//joystick_calibrate();

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
	*//*
	joystickposition joy_pos;
	joy_pos=joystickgetpos();
	
	menu_init();
	int o=0;
	int p=1;
	//int currenmenupos=0;
	//int enter=0;
	//cakefunc();
	while(1){
		//newgame
		//if 
		
		joy_pos=joystickgetpos();
		if(joy_pos.x>50){
			o=1;
		}else if(joy_pos.x<-50){
			o=-1;
		}
		if(joy_pos.y > 50) {
			p=p-1;
				if(p<2)
				{p=8;
				}
			
			} else if(joy_pos.y < -50) {
			p=p+1;
				if(p>8){p=0;}
		}
		if(joy_pos.x > -50 && joy_pos.x<50){
			o=0;
		}
		
		printf("x position is %d, and y position is %d \r \n",o, p);
		
		selmenu(&currentmenu ,o , p);
		
		//cakefunc();
	}*/
	UART_init(F_CPU);
	
	can_init();								//initialize the can
	
	can_message message;					//structs for holding the values
	can_message RX_message;					//--------- || -----------
	message.id = 2;
	message.length = 7;
	message.data[0] = 3;
	message.data[1] = 1;
	message.data[2] = 4;
	message.data[3] = 1;
	message.data[4] = 5;
	message.data[5] = 9;
	message.data[6] = 2;
											//setting the data to be sent in the struct and sending it
	//can_send(&message);
	printf("%d",RX_message.id);
	
	char l;
	//SPI_init();
	while(1)
	{	
		/*if(can_interrupt()){							//if a interrupt happens save the message and print it.
			CAN_recieve(&RX_message);
			
			l=RX_message.data[0];
			printf(RX_message.id,RX_message.data[0]);
		}
		_delay_ms(30);
		*/
		can_send(&message);
		CAN_recieve(&RX_message);
		l=RX_message.data[0];
		//printf("%d\n",RX_message.data[0]);
		_delay_ms(1000);
		printf("%d , %d %d %d %d %d %d \n",RX_message.data[0],RX_message.data[1],RX_message.data[2],RX_message.data[3],RX_message.data[4],RX_message.data[5],RX_message.data[6],RX_message.data[7]);
		
	}
		
}
