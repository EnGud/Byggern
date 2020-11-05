/*
 * SPI.h
 *
 * Created: 29.10.2020 10:24:37
 *  Author: harasa
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_init(void);
void SPI_write(char c);
char SPI_read(void);
void SPI_SLAVE_EN(uint8_t enable);



#endif /* SPI_H_ */