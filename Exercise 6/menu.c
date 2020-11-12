/*
 * menu.c
 *
 * Created: 08.10.2020 12:09:28
 *  Author: harasa
 */ 
#include <stdlib.h>
#include <stdio.h>
#include "Oled.h"
#include "menu.h"
#include <util/delay.h>


void menu_init(void)
{
	oled_reset();//clear the screen
	oled_pos(2,1);
	oled_print(">");
	mainmenu.title="Mainmenu";
	play.title = "play";
	hiscore.title= "HI-score";
	settings.title= "settings";
	dummy.title="dummy";
	//assign hierarcy:
	
	

	
	hierarcy(&play,&mainmenu,NULL);
	hierarcy(&settings,&mainmenu,NULL);
	hierarcy(&hiscore,&mainmenu,NULL);
	
	hierarcy(&dummy,&hiscore,NULL);
	hierarcy(&dummy,&settings,&cakefunc);
	
	printmenutoscreen(&mainmenu);
	currentmenu=mainmenu;
	/*
	
	
	
	*/
}

void hierarcy(struct menus * child, struct menus * parentname, void (* function)(void)){
	child->parent=parentname;
	parentname->children[parentname->numofchildren]=child;
	parentname->numofchildren++;
	child->fp = function;
}

/*
   oled_pos(0,1);
   oled_print("____");
   oled_pos(1,1);
   oled_print("|___ \");
   oled_pos(2,1);
   oled_print("  __) |");
   oled_pos(3,1);
   oled_print("/ __/");
   oled_pos(4,1);
   oled_print("|_____|");
   
    
*/
/*
0	////P O N G/////		
1	////////////////		
2	////////////////
3	/>Play//////////
4	////////////////
5	/settings///////
6	////////////////
7	/hi-score///////
8	////////////////
*/
/*
		
2	/	  ¤	¤ ¤
3	 ¸,.·'|'|'|·.,¸
4	;'·.,¸¸¸¸¸¸,.·';
5	;  U got Cake? ;
6	;	    ;)     ;
7	 '·.,¸¸¸¸¸¸,.·'
8	  +47 95486881
0	text: i do indeed ;)
*/
void cakefunc(void){
	
	oled_reset();//clear the screen
	oled_pos(0,1);
	oled_print("### | ##########");
	oled_pos(1,1);
	oled_print("### | ##########");
	oled_pos(2,1);
	oled_print("    | ");
	oled_pos(3,1);
	oled_print("===============");
	oled_pos(4,1);
	oled_print("    |");
	oled_pos(5,1);
	oled_print("### | ##########");
	oled_pos(6,1);
	oled_print("### | ##########");
	oled_pos(7,1);
	oled_print("+47 95486881");
	_delay_ms(100);
	
	
}


void selmenu(struct menus * CurrentMenu ,int JoystickDirectionx, int MenuPosition){
	
	pastmenu=*CurrentMenu;
	/*if((JoystickDirectionx == 1) && (*CurrentMenu->children[MenuPosition-2]->fp != NULL)){
		CurrentMenu->fp();
		
		*CurrentMenu = *CurrentMenu->children[MenuPosition-2];
	}*/
	if((JoystickDirectionx == 1 )&&(*CurrentMenu->children[MenuPosition-2]->title !=NULL)){
		*CurrentMenu = *CurrentMenu->children[MenuPosition-2];
			if((*CurrentMenu->fp != NULL))
			{
				CurrentMenu->fp();
				}
		
	}
	else if (JoystickDirectionx == -1){
		*CurrentMenu = mainmenu;
		
	}
	else
	{
	printcursor(MenuPosition, 0);	
	}
	
	
	if(strcmp(pastmenu.title,CurrentMenu->title)!=0){
	oled_reset();
	printmenutoscreen(CurrentMenu);
	}
	
	
}
void printcursor(int currentpos, int offset)
{
	oled_clearcol();
	oled_pos(currentpos + offset, 1);
	oled_print(">");
}
void printmenutoscreen(struct menus * nodename)
{
	//print current meny til oled_screen. vi kan bruke oled_pos og oled_print, 
	oled_pos(0,4);
	oled_print(nodename->title);
	for(int i=0; i<nodename->numofchildren;i++){
		oled_pos(i+2,4);
		oled_print(nodename->children[i]->title);
	}
	if(nodename->parent !=NULL){
		oled_pos(nodename->numofchildren+2,4);
		oled_print("return");
	}
}

