//this system is very WIP. The main functionality is there, but a lot of bugfixing is needed.

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "oled.h"
#include "CAN.h"
#include <util/delay.h>
#include "gameLogic.h"

void setup(void){}

bool Game = False;
int Score = 0;
int IRThreshold = 5;
int FirstTimeStart = 0;


void main(void){
//The main function for actually running the game. This function will loop for as long as score remains under 5. 
  void PlayGame(void){
    //Initial check to see if game should start
  if(FirstTimeStart == 0)
    Game = True;
    FirstTimeStart++;
  }
    while(Game=="True"){
      can_send(joystick);   //
      can_send(motor_pos);   //
      can_send(servo);      // These three needs proper setup!!!!!!
      
      int IR_Status = can_receive(ir_status); //receives data from node 2 about IR status. ir_status is a struct. Needs fixing!
      
     int gamestatus = checkIfAlive(int maxScoreVariable, int IR_Status, int IRThreshold);
      if(gamestatus == 1){
        Game == "False"
        FirstTimeStart = 0;   //This is not a proper break! will still loop in game, instead of return to menu!
      }
    }
  //a simple function to show the latest live high-score on the screen. This resets when the system resets.
  void ShowHighScore(void){
    char ScoreAsChar = Score + '0';
    oled_print(ScoreAsChar);
    delay_ms_(2000);
    return
  }

}
