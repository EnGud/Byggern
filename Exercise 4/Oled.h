/*
 * Oled.h
 *
 * Created: 08.10.2020 10:08:26
 *  Author: harasa
 */ 
#ifndef OLED_H_
#define OLED_H_
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void oled_init(void);

void oled_reset(void);

void oled_write(char input);

void oled_print(char *symbol);

void oled_home(void);

void oled_goto_line(uint8_t line);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t line, uint8_t column);


#endif