/*
 * ADC.c
 *
 * Created: 12.11.2020 16:12:49
 *  Author: harasa
 */ 
#include "sam.h"



void adcinit(void){
	PMC -> PMC_PCER1 = PMC_PCER1_PID37;
	ADC->ADC_MR|=ADC_MR_FREERUN_ON;
	ADC->ADC_CHER|=ADC_CHER_CH0;
	
	
	ADC->ADC_CR|=ADC_CR_START;
	
	
	
	
}