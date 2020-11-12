/*
 * CAN.c
 *
 * Created: 29.10.2020 15:11:03
 *  Author: harasa
 */ 
#include "CAN.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MCP2515.h"

volatile int flag = 0;

ISR(INT0_vect){
	flag = 1;
}

uint8_t can_interrupt(){
	if (flag){
		flag = 0;
		return 1;
	}
	return 0;
}

void can_init(void){
	
	mcp2515_init();

	//can_setmodus(MODE_NORMAL);
	//mcp2515_write(MCP_CANINTE,MCP_RX_INT);
	
	
	// Disable global interrupts
	cli();
	// Interrupt on falling edge PD2
	MCUCR |=(1<<ISC01);
	MCUCR &=~(1<<ISC00);
	GICR |=(1<<INT0);
	sei();
	
}

void can_setmodus(char mode){
	
	mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK, mode);
	
	
}
void can_send(can_message * new_message){
	
	mcp2515_write(MCP_TXB0SIDL,new_message->id<<5);
	mcp2515_write(MCP_TXB0SIDH,new_message->id<<3);
	mcp2515_write(MCP_TXB0DLC,new_message->length);
	
	for(int i =0; i<new_message->length; i++){
		mcp2515_write(MCP_TXB0D0+i,new_message->data[i]);
	}
	 mcp2515_request_to_send();
	
}
void CAN_recieve(can_message * new_RX_message){
	if(mcp2515_read(MCP_CANINTF),MCP_RX0IF){
		_delay_ms(10);
		new_RX_message->id= (mcp2515_read(MCP_RXB0SIDH)<<3)|(mcp2515_read(MCP_RXB0SIDL)>>5);
		new_RX_message->length = mcp2515_read(MCP_RXB0DLC) & 0x0F;
		for(uint8_t i = 0; i<new_RX_message->length; i++){
			new_RX_message->data[i]= mcp2515_read(MCP_RXB0D0+i);
		}
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF,0);
		
	}
	
	
	
}