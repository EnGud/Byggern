/*
 * joystickdriver.h
 *
 * Created: 17.09.2020 13:03:11
 *  Author: harasa
 */ 


#ifndef JOYSTICKDRIVER_H_
#define JOYSTICKDRIVER_H_

typedef enum {joystickbutton, vbutton, hbutton} button_t;
	
int xmid, ymid;
typedef struct{
	
	int x;
	int y;
	char *direction;
	} joystickposition;

typedef struct {
	uint8_t left;
	uint8_t right;
} slider_position;


joystickposition joystick_getDirection(void);

void joystick_init(void);
joystickposition joystickgetpos(void);
int joystick_calibrate(void);
uint8_t joystick_button(button_t btn);

slider_position Joystick_getSliderPosition(void);

#endif /* JOYSTICKDRIVER_H_ */