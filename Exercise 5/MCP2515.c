#include "mcp2515.h"
#include <stdint.h> //trengs ikke i Atmel, fordi VSC er retard????
#include "UART.h"
#include "SPI.h"





uint8_t  mcp2515_init (){ //copied from slides
    uint8_t  value;
 SPI_init(); //  Initialize  SPI
 SPI_SLAVE_EN(1);

 mcp2515_set_mode(MODE_NORMAL);
 mcp2515_reset (); // Send  reset -command

 // Self -test
 mcp2515_read(MCP_CANSTAT);
 value = MCP_CANSTAT;
 if ((value & MODE_MASK)   !=  MODE_CONFIG) {
    printf("MCP2515  is NOT in  configuration  mode  after  reset!\n");
    return  1;
    }
    
    // More  initialization
    return  0;
 SPI_SLAVE_EN(0);
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
    SPI_Write(Data);

 SPI_SLAVE_EN(0);
 return 1;
}



void mcp2515_request_to_send(void){
 SPI_SLAVE_EN(1);

mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001000, 0b00001000);

 SPI_SLAVE_EN(0);
}



void mcp2515_bit_modify(uint8_t Address, uint8_t mask, uint8_t Data){
 SPI_SLAVE_EN(1);

 SPI_Write(MCP_BITMOD);
 SPI_Write(Address);
 SPI_Write(mask);
 SPI_WRITE(Data);


 SPI_SLAVE_EN(0);

}

int mcp2515_set_mode(uint8_t mode){
 
 
 
 mcp2515_bit_modify(MCP_CANCTRL, 0b11101110, mode | 0b1100);
 mcp2515_bit_modify(MCP_CANINTE, 0b11111111, 0b1);
 mcp2515_bit_modify(MCP_RXB0CTRL, 0b01100000);
   return 0;
}

void mcp2515_reset(){
 SPI_SLAVE_EN(1);

 SPI_write(MCP_RESET);

 SPI_SLAVE_EN(0);
}



int mcp2515_read_status(){
 SPI_SLAVE_EN(1);
 SPI_Write(MCP_READ_STATUS);
 int Status = SPI_read();

 SPI_SLAVE_EN(0);
 return Status;
}


// Used SPI; SPI_read(), SPI_write(), SPI_init()
