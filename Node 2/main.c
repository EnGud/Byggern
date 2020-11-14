/*
 * ARduinodueex6.c
 *
 * Created: 05.11.2020 11:37:47
 * Author : harasa
 */ 


#include "sam.h"
#include "printf_stdarg.h"
#include "uart.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "servo.h"
#include "ADC.h"

void delay(void);
int main(void)
{	
    /* Initialize the SAM system */ 
    SystemInit();
	CAN_MESSAGE rex_mess;
	
	configure_uart();
	initTimer1();
	can_init_def_tx_rx_mb(0x290561);//need an integer to set can_br as to set the baudrate. 0x290561
	//REG_PIOA_OER |=(1<<19)|(1<<20); //enabling pin 19 and 20 as output
    /* Replace with your application code */
    uint8_t x,y;
	//printf("%d",rex_mess.data[0]);
	uint32_t p;
	uint8_t o;
	adcinit();
	while (1) 
    {	
		//printf("hello world");
		/*delay();
		REG_PIOA_SODR |= (1 << 20)|(1 << 19); //setting bit 20 and 19 in the pioa register
		delay();
		REG_PIOA_CODR |= (1 << 20)|(1 << 19); //clearing the bit 20 and 19 in the port a register
		*/
		//can_receive(&rex_mess, 1);
		//printf(rex_mess.data[0],rex_mess.data[2],rex_mess.data[3],rex_mess.data[4],rex_mess.data[5],rex_mess.data_length);
		//PIOA |= (1<<20);
		//PWM->PWM_CDTYUPD[5]|=0x10eb;
		//REG_PWM_CDTYUPD5=0xAd1;
		//delay();
		//REG_PWM_CDTYUPD5=0x14d8;
		//delay();
		
		p=ADC->ADC_CDR[0];
		x=can_receive(&rex_mess,2);
		y=can_receive(&rex_mess,1);
		if(x==0){
			//printf(" X IS %d, Y IS %d\n\r",rex_mess.data[0],rex_mess.data[1]);
			REG_PWM_CDTYUPD5=2567+12*rex_mess.data[0];
		}
		if(y==0){
			//printf(" X IS %d, Y IS %d\n\r",rex_mess.data[0],rex_mess.data[1]);
			REG_PWM_CDTYUPD5=2567+12*rex_mess.data[0];
		}
		
			if(p<=1500){
				printf(" score is: %d\n\r", o);
				o=255-1;
			}
			
		//printf(" val of adc is: %d\n\r", p);
		
    }
}


void delay(void) {
	
	for (int t = 0; t < 100000; t++)
	{ 
		for (int i = 0; i < 100; i++) //about a half second delay
		{
			__asm__ volatile("nop\n\t"); // busy wait
		}
	}
}