#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_PAUSE		  20000
#define PULSE_MIN         900         
#define PULSE_MAX         2100  
#define PULSE_MID         1500
#define ADC_INPUT_MIN	  0
#define ADC_INPUT_MAX	  1023
#define SERVO_TEST_DELAY  2000

static inline void initTimer1(void);
static inline void servoTestPosition(int testDelay);
static inline void positionSensor(uint16_t positionVal);
static inline void initADC0(void);
static inline void showADCOnLED(int adcOutput);
static inline uint16_t readADC();

int main(void) {
	uint16_t adcValue;
	float slope = 1.0 * (PULSE_MAX - PULSE_MIN) / (ADC_INPUT_MAX - ADC_INPUT_MIN);
	DDRD = 0xff;
				
	initADC0();
	initTimer1();
	servoTestPosition(SERVO_TEST_DELAY);
	
	while (1) {	
		adcValue = readADC();	
		showADCOnLED(adcValue);		
		positionSensor(PULSE_MIN + slope * (adcValue));		
		}
	}

static inline void initTimer1(void) {
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

static inline void servoTestPosition(int testDelay) {
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

static inline void initADC0(void) {
	//Set reference voltage to AVCC.
	ADMUX |= (1 << REFS0);
	//ADC clock prescaler 8.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	//Enable ADC
	ADCSRA |= (1 << ADEN);
}

static inline void showADCOnLED(int adcOutput) {
	//LED test circuit.
	//Make 8-bit through padding and light LED.
	uint8_t ledOutput;
	ledOutput = (adcOutput >> 7);
	PORTD = 0;
	for (uint8_t i = 0; i <= ledOutput; i++) {
		PORTD |= (1 << i);
	}
}

static inline uint16_t readADC()
{
	//ADC conversion
	//Start Conversion
	ADCSRA |= (1 << ADSC);
	//Wait for data
	do { } while (bit_is_set(ADCSRA, ADSC));
	//Store Data
	return ADC;
}
