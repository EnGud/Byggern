#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "oled.h"
#include "CAN.h"

void setup(void){}


void main(void){
//The main function for actually running the game. This function will loop for as long as score remains under 5. 
  void PlayGame(void){
    while(Game=="True"){
      can_send(joystick);
      CAN_recieve(somestruct);
        
    }
  }
  //a simple function to show the latest live high-score on the screen. This resets when the system resets.
  void ShowHighScore(void){
    CAN_recieve(score_variable);?
    oled_print(
  }

}
