#include "Encoder.h"
#include "sam.h"

#define OutputEnable PD0
#define Reset PD1
#define Select PD2
#define Enable PD9
#define Direction PD10

int initialValue = 0;
//DACC_MR;
//DACC_CHER;
//DACC_CDR;

int Max_Encoder = 0;
int Min_Encoder = 0;


void Encoder_init(){
DDRD |= (1<<OutputEnable)|(1<<Reset)|(1<<Select);
DDRC |= (0b00000000<<DDRC)

PORTD &= ~(1<<Reset);
PORTD |= (1<<Reset);
PORTD |= (1<<OutputEnable);

DACC_MR |= (0<<5);
Encoder_Reset();
}



void Encoder_Reset(){
    PORTD |= (1 << Reset); //Sets reset pin high
    PORTD &= ~( 1 << Reset); //And sets low
}

void Encoder_Sleep(){

}

void Encoder_MaxMinCalibrate(){

 if (fuckaimspice > Max_Encoder){
    Max_Encoder = fuckaimspice;
 }
 else if (fuckaimspice < Min_Encoder){
    Min_Encoder = fuckaimspice;
 }
}

int Encoder_Read(){
 int EncoderRead = 0b111111110;
 int EncoderRead &= PORTC;
return fuckaimspice;
}

void Encoder_Map(Value){
//float Relation = 1.0*(Max_Encoder - Min_Encoder)/(ADC_INPUT_MAX-ADC_INPUT_MIN);
float Current_Pos = 1.0 * Value;
}

void Encoder_Write(int data){
DACC_CHER |= (0b00000001); 
DACC_CDR = data;
DACC_CHER &= ~(0b00000001);
}