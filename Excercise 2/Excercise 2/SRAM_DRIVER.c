#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "SRAM_DRIVER.h"

void SRAM_INIT(void){
SFIOR |= (1<<XMM2);
MCUCR |= (1<<SRE);
}


int SRAM_WRITE (uint16_t adress, char data){
	if ( (adress > 0x1FF) || (adress < 0x1800) ){   // checks if data is within limits
		printf("Error! Adress not within pre-defined limits. See manual to find the pre-defined limits.");
		return 1;
	}

volatile char* external_ram = 0x1800;
external_ram[adress] = data;
	return 0;
}

char SRAM_READ(char adress){
	if ( (adress > 0x1FF) || (adress < 0x1800) ){
		printf("Error! Adress not within pre-defined limits. See manual to find the pre-defined limits.");
	return 1;
	}
	volatile char* external_ram;
	return external_ram[adress];
}



void SRAM_Clean(){
	for (int i = 0x1800; i= 0x1FF; i++){
		
	}
}

void SRAM_Test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}