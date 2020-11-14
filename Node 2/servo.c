/*
 * servo.c
 *
 * Created: 08.11.2020 16:55:33
 *  Author: harasa
 */ 
#include "sam.h"
#include "servo.h"


void initTimer1(void) {
	//nee to use pin 44 and pin 45, 11 og 12 on the shield PC19 and PC18 PWMH5=19 PWMH6=18
	//REG_PMC_PCER0 |=(1<<13);
	//PIOC->PIO_PDR |= PIO_PC19; //disablen and choose B pwmL2
	//PIOC->PIO_PDR |= PIO_PC18; //disablen and choose B pwmL2
//
	//PIOC->PIO_ABSR|= PIO_PC19; //choose b 
	//PIOC->PIO_ABSR|= PIO_PC18; //choose b
//
	//REG_PMC_PCER1|=0b10000;
	//REG_PWM_CMR5|=0b111; //prescale 128
	//REG_PWM_CPRD5|=0X3345; //set cpdr period
	//REG_PWM_CDTY5|=656; //set cdty duty cycle
	//REG_PWM_ENA|=0x10;	//enable ch5 pwm5
	
	PMC -> PMC_PCER0 = ID_PIOC;
	PMC -> PMC_PCER1 = PMC_PCER1_PID36;
	PIOC ->PIO_ABSR  = PIO_PC19;
	PIOC ->PIO_PDR  = PIO_PC19;
	
	PWM ->PWM_CH_NUM[5].PWM_CMR = (PWM_CMR_CPOL) | PWM_CMR_CPRE_MCK_DIV_32;
	PWM ->PWM_CH_NUM[5].PWM_CPRD = 0xcd14;
	PWM ->PWM_CH_NUM[5].PWM_CDTY = 0xAd1;//0x10eb;0xAd1
	PWM -> PWM_ENA = PWM_ENA_CHID5;
	
	//->PWM_CMR_CPRE_MCK_DIV_128 |=1;
	
	/*
	//Timer1 (16bit) counting up to max 20ms
	//Set to fast PWM, counter max in ICR1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	//Prescaler of 1, reads in uS (microseconds).
	TCCR1B |= (1 << CS10);
	//Set max value to make a delay between pulses.
	ICR1 = PULSE_PAUSE;
	//OC1A connected to PB1
	TCCR1A |= (1 << COM1A1);
	//Set output on PB1
	DDRB |= (1 << PB1);*/
}

void servoTestPosition(int testDelay) {
	/*//Displays the extreme values for the servo position (MIN, MAX and CENTRE)
	//With a input delay
	OCR1A = PULSE_MID;
	_delay_ms(testDelay);
	OCR1A = PULSE_MIN;
	_delay_ms(testDelay);
	OCR1A = PULSE_MAX;
	_delay_ms(testDelay);*/
}

static inline void positionSensor(uint16_t positionVal) {
	/*//Takes servo position value and filters the input value.
	//Does not allow values outside of the range.
	if ((positionVal <= PULSE_MAX) & (positionVal >= PULSE_MIN)) {
		OCR1A = positionVal;
	}*/
}
void initADC0(void) {
	/*//Set reference voltage to AVCC.
	ADMUX |= (1 << REFS0);
	//ADC clock prescaler 8.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	//Enable ADC
	ADCSRA |= (1 << ADEN);*/
}
static inline uint16_t readADC(void)
{
	/*//ADC conversion
	//Start Conversion
	ADCSRA |= (1 << ADSC);
	//Wait for data
	do { } while (bit_is_set(ADCSRA, ADSC));
	//Store Data
	return ADC;*/
	return 0;
}