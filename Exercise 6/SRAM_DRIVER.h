/*
 * sram.h
 *
 * Created: 03.09.2020 15:00:32
 *  Author: harasa
 */ 



#ifndef SRAM_DRIVER_H_
#define SRAM_DRIVER_H_



void SRAM_INIT(void);
void SRAM_WRITE (uint16_t adress, char data);
char SRAM_READ(char adress);
void SRAM_Test(void);


#endif /* SRAM_DRIVER_H_ */