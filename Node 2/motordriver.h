/*
 * motordriver.h
 *
 * Created: 14.11.2020 15:31:53
 *  Author: harasa
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_


void initdac(void);
void sendDAC(uint32_t data);

uint16_t motor_read_rotation();
void encoderinit(void);
void resetencoder(void);

void delay_micros(uint32_t us);

void encoderinit(void);
int motormaxmin(int curr);
void motorcalib();
void setmotordir(uint8_t direction);

#endif /* MOTORDRIVER_H_ */