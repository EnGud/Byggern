#ifndef Encoder_H_
#define Encoder_H_

#define DACC_CHER = 0x400C8010;
#define DACC_MR = 0x400C8004;
#define DACC_CDR = 0x400C8020;
#define DACC_CR = 0x400C8000;

#endif

void Encoder_init()
void Encoder_Reset()
void Encoder_Sleep()
void Encoder_Write(int data)
void Encoder_Map(Value)
int Encoder_Read()
void Encoder_MaxMinCalibrate()