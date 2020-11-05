/*
 * menu.h
 *
 * Created: 08.10.2020 12:09:45
 *  Author: harasa
 */ 


#ifndef MENU_H_
#define MENU_H_


struct menus{
		char * title;
		struct menus * parent;
		struct menus * children[8];
		void(*fp)(void);
		int numofchildren;	
	}mainmenu,play,settings,hiscore,dummy, currentmenu, pastmenu;
	
void menu_init(void);	
void selmenu(struct menus * CurrentMenu ,int JoystickDirectionY, int MenuPosition);
void hierarcy(struct menus * child, struct menus * parentname, void(* function)(void));
void printmenutoscreen(struct menus * nodename);
void printcursor(int currentpos, int offset);
void cakefunc(void);
#endif /* MENU_H_ */