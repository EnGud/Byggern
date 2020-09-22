/*
 * ADC_driver.h
 *
 * Created: 17.09.2020 11:39:55
 *  Author: harasa
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_


typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} channel_t;
	
void ADC_read(channel_t channel);
	
char get_adcdata(void);

#endif /* ADC_DRIVER_H_ */