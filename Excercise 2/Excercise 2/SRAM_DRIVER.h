/*
 * SRAM_DRIVER.h
 *
 * Created: 03.09.2020 15:30:46
 *  Author: Fucktart Widnows 10
 */ 


#ifndef SRAM_DRIVER_H_
#define SRAM_DRIVER_H_




int SRAM_Write (uint16_t DataWrite (uint16_t Adress, char data) );
char SRAM_Read(uint16_t DataRead (char Adress));
void SRAM_Test(void);


#endif /* SRAM_DRIVER_H_ */