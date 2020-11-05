/*
 * MCP2515.c
 *
 * Created: 29.10.2020 12:28:17
 *  Author: harasa
 */ 
#include "MCP2515.h"
#include <stdint.h> //trengs ikke i Atmel, fordi VSC er retard????
#include "UART.h"
#include "SPI.h"
#include <util/delay.h>





uint8_t  mcp2515_init (){ //copied from slides
	uint8_t  value;
	SPI_init (); //  Initialize  SPI
	UART_init(4915200);
	mcp2515_reset();

	// Send  reset -command
	value = mcp2515_read(MCP_CANSTAT);
	
	if ((value & MODE_MASK)   !=  MODE_CONFIG) {
		printf("MCP2515  is NOT in  configuration  mode  after  reset!\n");
		return  1;
	}
	printf("do");
	SPI_SLAVE_EN(1);
	//mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK, MODE_LOOPBACK);
	mcp2515_bit_modify(MCP_CANCTRL, 0b11101110, MODE_LOOPBACK | 0b1100);
	mcp2515_bit_modify(MCP_RXB0CTRL,0b01100000,0b01100000);
	SPI_SLAVE_EN(0);
	//mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK);
	value = mcp2515_read(MCP_CANSTAT);
	
	if ((value & MODE_MASK)  !=  MODE_LOOPBACK) {
		printf("MCP2515  after  reset!\n");
		return  1;
	}
		
	printf("done");	
	// More  initialization
	return  0;

}




uint8_t  mcp2515_read(uint8_t address){ //Copied from slides
	uint8_t  result;
	SPI_SLAVE_EN(1);
	SPI_write(MCP_READ); // Send  read  instruction
	SPI_write(address); // Send  address
	result = SPI_read (); // Read  result

	SPI_SLAVE_EN(0);
	return  result;
}



int mcp2515_write(uint8_t Adress, uint8_t Data){
	SPI_SLAVE_EN(1);
	SPI_write(MCP_WRITE);
	SPI_write(Adress);
	SPI_write(Data);

	SPI_SLAVE_EN(0);
	return 1;
}



void mcp2515_request_to_send(){
	SPI_SLAVE_EN(1);

	mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001000, 0b00001000);


	SPI_SLAVE_EN(0);
}



void mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data){
	SPI_SLAVE_EN(1);

	SPI_write(MCP_BITMOD);
	SPI_write(adress);
	SPI_write(mask);
	SPI_write(data);

	SPI_SLAVE_EN(0);

}



void mcp2515_reset(){
	SPI_SLAVE_EN(1);

	SPI_write(MCP_RESET);

	SPI_SLAVE_EN(0);
	_delay_ms(10);	
}



int mcp2515_read_status(){
	SPI_SLAVE_EN(1);
	SPI_write(MCP_READ_STATUS);
	int Status = SPI_read();

	SPI_SLAVE_EN(0);
	return Status;
}


// Used SPI; SPI_read(), SPI_write(), SPI_init()