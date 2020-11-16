/*
 * motordriver.c
 *
 * Created: 14.11.2020 14:35:08
 *  Author: harasa
 */ 
#include "sam.h"
#define reset 1
#define select 2
#define OE 0
#define dir 10

#include "motordriver.h"
#include "uart.h"


volatile int maximum,minimum,pos;//helpers for motorcalibrate.

void delay_micros(uint32_t us){
	uint32_t i,k;
	for(i = 0; i < us; i++){
		for(k=0;k<10;k++){
		__asm__ volatile("nop\n\t"); // busy wait
		}
	}
}

void initdac(void){
	PMC -> PMC_PCER1 = PMC_PCER1_PID38;//enablePMCclock
	DACC->DACC_MR|=DACC_MR_USER_SEL_CHANNEL1;//set channel 0
	DACC->DACC_MR|=DACC_MR_WORD_HALF; //use half word only 16lsb
	DACC->DACC_MR|=DACC_MR_REFRESH_Msk|0x00000f00; //set the REFRESH to 15
	DACC->DACC_CHER|=DACC_CHER_CH1;
	
	
	
}

void sendDAC(uint32_t data){
	
	DACC->DACC_CDR=data;
	//REG_DACC_CDR |=data;
	
}

uint16_t motor_read_rotation(){
	uint8_t high,low;
	int16_t encoderread;
	
	//return positive or negative 16 bit val for the rotation
	//to read the encoder:
	//set!OE low to get high byte
	REG_PIOD_CODR|=(1<<OE);
	//set sel low to get high byte
	REG_PIOD_CODR|=(1<<select);
	//wait 20microsecs
	delay_micros(20);
	//read MSB
	high= REG_PIOC_PDSR;
	//set SEL high to get low byte
	REG_PIOD_SODR|=(1<<select);
	//wait another 20microsex
	delay_micros(20);
	//read LSB
	low=REG_PIOC_PDSR;
	//toggle !RST to reset encoder
	resetencoder();
	//set !OE high to disble output of encoder
	REG_PIOD_SODR|=(1<<OE);
	//return the recieved data.
	encoderread=(int16_t)(high)|(low);	
	
	return encoderread;
	
}


void resetencoder(void){
	
	REG_PIOD_CODR |= (1 << reset); //set to low
	delay_micros(60);
	REG_PIOD_SODR|=(1<<reset); //set to high
	
}

void encoderinit(void){
	
	//PMC -> PMC_PCER0 = ID_PIOD;
	REG_PIOD_OER |=(1<<OE)|(1<<reset)|(1<<select)|(1<<dir);//enable !OE,!reset,sel,and direction as output
	REG_PIOC_ODR |=0b11111110;//pin 0-7 in port c to input
	
	REG_PIOD_SODR|=(1<<OE);
	resetencoder();
	
	
}


int motormaxmin(int curr){
	int max=0,min=0;
	
	if(curr>max){
		max=curr;
		return max;
	}
	else if(curr<min){
		min=curr;
		return min;
	}
	return 0;
}
void motorcalib(){
	
	for(uint8_t i=0 ; i<255;i++){
		setmotordir(1);
		sendDAC(100);
		motor_read_rotation(pos);	//encoderread
		maximum=motormaxmin(pos);
	}
	for(uint8_t r=0 ; r<255;r++){
		setmotordir(0);
		sendDAC(100);
		motor_read_rotation(pos);//encoderead
		minimum=motormaxmin(pos);
	}
	
	
	
	
}
void setmotordir(uint8_t direction){
	if(direction ==1){
		REG_PIOD_SODR|=(1<<dir);//toggle pin dir
	}
	else{
		REG_PIOD_CODR|=(1<<dir);//pin dir is 0
	}
	
}

