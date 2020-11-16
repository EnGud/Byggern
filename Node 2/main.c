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
#include "motordriver.h"



void delay(void);
//uint32_t ifgoal(uint32_t adcsample,uint8_t counter);
int main(void)
{	
    /* Initialize the SAM system */ 
    SystemInit();
	printf("haha");
	CAN_MESSAGE rex_mess;//holder strut for the data from the can
    uint8_t joyx,joyy;
	uint32_t adcp=1600;
	uint8_t holdo=0,countl=0;
	int16_t encorot,testhjk;
	configure_uart(); //initialsize the uart
	initTimer1();//initialize the PWM
	can_init_def_tx_rx_mb(0x290561);//need an integer to set can_br as to set the baudrate. 0x290561 //initialize the can
	adcinit();//initialize the adc
	initdac();
	REG_PIOC_ODR |=0b11111110;
	encoderinit();
	//sendDAC(0);//low voltage on the dac i think, upper is 2^16-1
	while (1) 
    {	
		//printf("hello world");
		/*delay();
		
		*/
		//can_receive(&rex_mess, 1);
		//printf(rex_mess.data[0],rex_mess.data[2],rex_mess.data[3],rex_mess.data[4],rex_mess.data[5],rex_mess.data_length);
		//PIOA |= (1<<20);
		//PWM->PWM_CDTYUPD[5]|=0x10eb;
		//REG_PWM_CDTYUPD5=0xAd1;
		//delay();
		//REG_PWM_CDTYUPD5=0x14d8;
		
		adcp=ADC->ADC_CDR[0];
		joyx=can_receive(&rex_mess,2);
		joyy=can_receive(&rex_mess,1);
		if(joyx==0){
			printf(" X IS %d, Y IS %d\n\r",rex_mess.data[0],rex_mess.data[1]);
			REG_PWM_CDTYUPD5=5149-12*rex_mess.data[0];
		}
		if(joyy==0){
			printf(" X IS %d, Y IS %d\n\r",rex_mess.data[0],rex_mess.data[1]);
			REG_PWM_CDTYUPD5=5419-12*rex_mess.data[0];
		}
		if(adcp<1200){							//treshold
			holdo=1;
			//printf("%d\n\r",o);
		}
		else{
		holdo=0;
		}
		if(holdo==1){
			countl=countl+1;
			
			//printf("%d\n\r",countl);
			delay_micros(200);
		}
		
		if(rex_mess.data[1]>125){
		setmotordir(1);
		sendDAC(1000);
		}
		else if(rex_mess.data[1]<75){
		setmotordir(0);
		sendDAC(1000);
		}
		else{
			sendDAC(0);
		}
		
		//testhjk=REG_PIOC_PDSR;
		//encorot=motor_read_rotation();
		//if(encorot!=0){
			//printf("h%x\r\n",testhjk);
		//}
	}
}



	



