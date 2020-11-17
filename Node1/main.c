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

int main(void)
{	
	
	UART_init(F_CPU);
	
	can_init();								//initialize the can
	
	joystick_init();
	joystick_calibrate();
	joystickposition joy_pos;
	can_message message;					//structs for holding the values
	can_message RX_message;					//--------- || -----------
	message.id = 1;
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
	
	uint8_t x1,y1;
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
		joy_pos=joystickgetpos();
		x1=joy_pos.x+100;
		y1=joy_pos.y+100;
		
		
		message.data[0]=x1;
		message.data[1]=y1;
		can_send(&message);
		
		//CAN_recieve(&RX_message);
		//l=RX_message.data[0];
		//printf("%d\n",RX_message.data[0]);
		//_delay_ms(1000);
		//printf("%d , %d %d %d %d %d %d \n",RX_message.data[0],RX_message.data[1],RX_message.data[2],RX_message.data[3],RX_message.data[4],RX_message.data[5],RX_message.data[6],RX_message.data[7]);
		
	}
		
}
