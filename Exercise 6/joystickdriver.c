/*
 * joystickdriver.c
 *
 * Created: 17.09.2020 13:02:53
 *  Author: harasa
 */ 
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_driver.h"
int xmid, ymid;
#include "joystickdriver.h"
#include "UART.h"
#include <util/delay.h>

#define test_bit( reg, bit ) (reg & (1 << bit));

void joystick_init(void)
{
	ADC_init();
	
	
	
	
	
}

int joystick_calibrate(void)
{
 ADC_read(CHANNEL4);
 xmid= get_adcdata();
 ADC_read(CHANNEL1);
 ymid= get_adcdata();	
	return 0; 
}

uint8_t joystick_button(button_t btn)
{
	switch(btn)
	{
		case joystickbutton:
			if(!(PINB |(1<<PINB2))) return 1;
		case vbutton:
			if ((PINB & (1<<PINB1))) return 1;	
		case hbutton:
			if((PINB & (1<<PINB0))) return 1;
		default:
			//printf("not valid btn");
			return 0;
	}
	
}
joystickposition joystickgetpos(void)
{ 
	joystickposition pos;
	
	int x,y;
	ADC_read(CHANNEL4);
	_delay_us(40);
	x= get_adcdata();
	ADC_read(CHANNEL1);
	_delay_us(40);
	y= get_adcdata();
	
	if(x>xmid+1)
	{
		pos.x=100*(x-xmid)/(0xff-xmid);
	}
	else if (x<xmid+1){
	pos.x=100*(x-xmid)/(xmid-0);
		
	}
		else {
					
			pos.x=0;
		}


	if(y>ymid+1)
	{
		pos.y=100*(y-ymid)/(0xff-ymid);
	}
	else if (y<ymid+1){
		pos.y=100*(y-ymid)/(ymid-0);
		
	}
	else {
		
		pos.y=0;
	}		
		
	return pos;
	
	
}

joystickposition joystick_getDirection(void) {
	joystickposition position;
	
	//Get actual position of joystick
	position = joystickgetpos();
	
	if(position.x < -50) {
		position.direction = "LEFT";
		
		} else if(position.x > 50) {
		position.direction = "RIGHT";
		
	}
	
	if(position.y < -50) {
		position.direction = "DOWN";
		
		} else if(position.y > 50) {
		position.direction = "UP";
		
	}
	
	
	if(position.x == 0 && position.y == 0){
		position.direction = "NEUTRAL";
		
	}
	
	
	return position;
}


slider_position Joystick_getSliderPosition(void) {
	slider_position position;
	uint8_t l, r;
	
	//Read left slider from channel 2
	ADC_read(CHANNEL2);
	
	l = get_adcdata();
	//Read right slider from channel 3
	ADC_read(CHANNEL3);
	r=get_adcdata();
	//Calculate position percentage
	position.left = 100 * l / 0xFF;
	position.right = 100 * r / 0xFF;
	
	return position;
}





//creating 
