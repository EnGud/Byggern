/*
 * menu.c
 *
 * Created: 08.10.2020 12:09:28
 *  Author: harasa
 */ 
#include <stdlib.h>
#include <stdio.h>
#include "oled.h"
#include "menu.h"
#include "joystick.h"


void menu_init(void)
{
	oled_reset();//clear the screen
	oled_pos(2,1);
	oled_print(">");
	mainmenu.title="Mainmenu";
	play.title = "play";
	hiscore.title= "HI-score";
	settings.title= "settings";
	//assign hierarcy:
	
	hierarcy(&play,&mainmenu,NULL);
	hierarcy(&settings,&mainmenu,NULL);
	hierarcy(&hiscore,&mainmenu,NULL);
	
	
	printmenutoscreen(&mainmenu);
	 currentmenu=mainmenu;
	/*
	
	
	
	*/
}

void hierarcy(struct menus *child, struct menus *parentname, int(* function)()){
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



void MenuCurrent(struct menus *CurrentMenu ,char JoystickDirectionY, int MenuPosition){



    if(JoystickDirectionY == "RIGHT"){
        *currentMenu = *currentMenu->Children[MenuPosition];
        oled_clear();
        printmenutoscreen(&CurrentMenu);
        printcursor(MenuPosition+1, 2);
        }
    elseif((JoystickDirection == "RIGHT") & (*CurrentMenu->Children[MenuPosition]->fp != NULL)){
        
    }  
    elseif (JoystickDirectionY == "LEFT"){
        *CurrentMenu = *CurrentMenu->parent;
        oled_clear();
        printmenutoscreen(&CurrentMenu);
        printcursor(MenuPosition+1, 2);
        }
    else{
    }
}
//hvilken meny 


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
void printcursor(int currentpos, int offset)
{
	oled_clearcol();
	oled_pos(currentpos + offset, 1);
	oled_print(" >");
}
int navigatemenu()
{	joystickposition joy_pos;
	joy_pos = joystickgetpos();
	if(joy_pos.direction=="UP"){
		return 1;		//navigere menyen med joysticken.
	}
	else{
		return 0;
	}
}

