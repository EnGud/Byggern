#include "fonts.h"
#include "Oled.h"
#define FONTWIDTH 8

volatile char *OLED_Command =(char *) 0x1000;

volatile char *OLED_Data =(char *) 0x1200;


int InitAdressArray[] = {0xae, 0xa1, 0x12, 0xc8, 0xa8, 0x3f, 0xd5, 0x80, 0x81, 0x50, 0xd9, 0x21, 0x20, 0x02, 0xdb, 0x30, 0xad, 0x00, 0xa4, 0xa6, 0xaf};

uint8_t col, page;
void oled_reset();
void oled_init(void)
{
	for (int i=0; i<=21; i++){
		*OLED_Command = InitAdressArray[i];
	}
	

	oled_reset();
	//oled_home();
}

void oled_write(char input){
	for (int i=0; i<FONTWIDTH; i++){
		*OLED_Data = pgm_read_byte(&font8[input-' '][i]);
	}
}

void oled_print(char *symbol){ //printer symbol til oled ved å bruke.
	int i = 0;

	while(symbol[i] != '\0'){
		oled_write(symbol[i]);
		i++;
	}
	
}



void oled_reset(void){
	for(int page= 0; page <8; page++){
		*OLED_Command = (0xB0+ page);
		
		for(int i=0;i<128; i++)
		{
			*OLED_Data=0x00;
		}
		
	}
}


void oled_home(void){
	*OLED_Command= 0x21;
	*OLED_Command= 0x00;
	*OLED_Command= 0x7f;
	*OLED_Command= 0x22;
	*OLED_Command= 0x00;
	*OLED_Command= 0x07;

}

void oled_goto_line(uint8_t line){
	oled_home();
	if(line<8){
		page =line;//save page
		*OLED_Command=0x00; //set lower column start adress
		*OLED_Command=0x10; //set higher column start adress
		*OLED_Command= 0xB0 |line; //set page adress.
	}
}


void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for (int i=0; i<128; i++){
		*OLED_Data = 0x00;
	}
}
void oled_clearcol()
{
	for(uint8_t j=0; j<8; j++){
		oled_pos(j, 0);
		
		for (int i = 0; i < FONTWIDTH*2; i++){
			*OLED_Data = 0x00;
		}
	}

}

void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	
	if(column<128/FONTWIDTH)
	{	//save page
		col=column*(FONTWIDTH);
		//set lower column start adress
		*OLED_Command= 0x00 + (column*(FONTWIDTH)>>4);
		//set higher column start adress
		*OLED_Command= 0x10 + (column*(FONTWIDTH)>>4);
	}
	
}

