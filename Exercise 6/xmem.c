/*
 * xmem.c
 *
 * Created: 10.09.2020 10:26:33
 *  Author: harasa
 */ 
#include "SRAM_DRIVER.h"



void init_xmem(void)
{
MCUCR |=(1<<SRE); //enable external memory.
SFIOR |=(1<<XMM2); //enable only, the pin4 to 7 is used in memory access so the jtag does not crash.
SRAM_Test();	//test the ext ram
}

