/*
 * servo.c
 *
 * Created: 08.11.2020 16:55:33
 *  Author: harasa
 */ 
#include "sam.h"
#include "servo.h"


void initTimer1(void) {
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
	DDRB |= (1 << PB1);
}

void servoTestPosition(int testDelay) {
	//Displays the extreme values for the servo position (MIN, MAX and CENTRE)
	//With a input delay
	OCR1A = PULSE_MID;
	_delay_ms(testDelay);
	OCR1A = PULSE_MIN;
	_delay_ms(testDelay);
	OCR1A = PULSE_MAX;
	_delay_ms(testDelay);
}

static inline void positionSensor(uint16_t positionVal) {
	//Takes servo position value and filters the input value.
	//Does not allow values outside of the range.
	if ((positionVal <= PULSE_MAX) & (positionVal >= PULSE_MIN)) {
		OCR1A = positionVal;
	}
}
void initADC0(void) {
	//Set reference voltage to AVCC.
	ADMUX |= (1 << REFS0);
	//ADC clock prescaler 8.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	//Enable ADC
	ADCSRA |= (1 << ADEN);
}
static inline uint16_t readADC(void)
{
	//ADC conversion
	//Start Conversion
	ADCSRA |= (1 << ADSC);
	//Wait for data
	do { } while (bit_is_set(ADCSRA, ADSC));
	//Store Data
	return ADC;
}