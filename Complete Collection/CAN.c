#include "mcp2515.h"
#include <stdint.h> //trengs ikke i Atmel, fordi VSC er retard????

uint8_t  mcp2515_init (){ //copied from slides
    uint8_t  value;
SPI_init (); //  Initialize  SPI
mcp2515_reset (); // Send  reset -command

// Self -test
mcp2515_read(MCP_CANSTAT , &value);

if ((value & MODE_MASK)   !=  MODE_CONFIG) {
    printf("MCP2515  is NOT in  configuration  mode  after  reset!\n");
    return  1;
    }
    
    // More  initialization
    return  0;
    }

uint8_t  mcp2515_read(uint8_t  address, uint8_t Data){ //Copied from slides
    uint8_t  result;
SPI_SLAVE_EN(1);
    SPI_write(MCP_READ); // Send  read  instruction
    SPI_write(address); // Send  address
    result = SPI_read (); // Read  result

SPI_SLAVE_EN(0);
    return  result;
    }


void mcp2515_write(){


}



void mcp2515_request_to_send(){


}



void mcp2515_bit_modify(){


}



void mcp2515_reset(){


}



void mcp2515_read_status(){


}


// Used SPI; SPI_read(), SPI_write(), SPI_init()