/*
 * menu.h
 *
 * Created: 08.10.2020 12:09:45
 *  Author: harasa
 */ 


#ifndef MENU_H_
#define MENU_H_
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

struct menuitem{
		char * title;
		struct menuitem * parent;
		struct menuitem * children[8];
		int(*fp)();
		int numofchildren;	
	}mainmenu,newgame,settings,highscore, about, calibration,pid,modeselectm misc currentmenu;
	





#endif /* MENU_H_ */