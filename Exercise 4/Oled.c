#include <avr/pgmspace.h>

volatile char* OLED_Command = 0x1000

volatile char* OLED_Data = 0x1200



char* InitAdressArray[] = {0xae, 0xa1, 0x12, 0xc8, 0xa8, 0x3f, 0xd5, 0x80, 0x81, 0x50, 0xd9, 0x21, 0x20, 0x02, 0xdb, 0x30, 0xad, 0x00, 0xa4, 0xa6, 0xaf}

int row, line, column;

void oled_init()   {    
	for (int i=0; i<=sizeof(InitAdressArray); i++){
	*OLED_Command = InitAdressArray[i];
	}
	//fuck KÅRE sine m_eininGER og hans GERMANY og nazist.

//oled_clear();
//oled_home();
}

void oled_write(char input){
for (int i=0; i<FONTWIDTH; i++){
 *OLED_Data = pgm_read_byte(&font[input-' '][i]);
 }	
}

void oled_print(char* read){
int i = 0;

while(read[i] != '\0'){
oled_write(read[i]);
i++;	
}
	
}



void oled_reset(){
	
}
	
	
void oled_home(){
line = 0;
column = 0;


}
	
void oled_goto_line(int line){
	
}

void oled_goto_column(int column){
}
	
void oled_clear_line(line){
for (i=0; i<128; i++){
	*OLED_Data = 0x00;
}
}
	
void oled_pos(int row, int column){
	
}
	
void  OLED_print_arrow(uint8_t row , uint8_t  col){
	OLED_pos(row , col);
	OLED_write_data (0 b00011000);
	OLED_write_data (0 b00011000);
	OLED_write_data (0 b01111110);
	OLED_write_data (0 b00111100);
	OLED_write_data (0 b00011000);
	}




void oled_brightness(){
}

	
