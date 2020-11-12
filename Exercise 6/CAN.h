/*
 * CAN.h
 *
 * Created: 29.10.2020 15:11:26
 *  Author: harasa
 */ 


#ifndef CAN_H_
#define CAN_H_
#include <avr/io.h>

typedef struct CAN_message{
	uint8_t id;
	uint8_t length;
	uint8_t data[8];
	
}can_message;

uint8_t can_interrupt();
void can_init(void);
void can_setmodus(char mode);
void can_send(can_message * new_message);
void CAN_recieve(can_message * new_RX_message);
#endif /* CAN_H_ */