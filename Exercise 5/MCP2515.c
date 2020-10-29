#include "mcp2515.h"
#include <stdint.h> //trengs ikke i Atmel, fordi VSC er retard????





uint8_t  mcp2515_init (){ //copied from slides
    uint8_t  value;
 SPI_init (); //  Initialize  SPI
 SPI_SLAVE_EN(1);

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



void mcp2515_request_to_send(int TransmitChannel, int HIGHORLOW){
 SPI_SLAVE_EN(1);

 mcp2515_write(TransmitChannel, HIGHORLOW);

 SPI_SLAVE_EN(0);
}



void mcp2515_bit_modify(){
 SPI_SLAVE_EN(1);

 SPI_Write();

 SPI_SLAVE_EN(0);

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