#include "Motor.h"
#include "Encoder.h"

#define OutputEnable PD0
#define Reset PD1
#define Select PD2
#define Enable PD9
#define MotorDirection PD10

int ActualSpeed;




void Motor_init(){


}

void Motor_BorderSetup{

 for (i=100; i<=200, i++){
    Motor_SetPosition(i);
    Encoder_Read();
    Encoder_MaxMinCalibrate();
 }
 
 for (i=100; i>=0, i--){//bytt tall
    Motor_SetPosition(i);
    Encoder_Read();
    Encoder_MaxMinCalibrate();
 }  
}


void Motor_Enable(){
    DDRD |= (1<<Enable);
}

void Motor_Disable(){
    DDRD &= ~(1<<Enable);
}

void Motor_SetDirection(Direction){

    if(Direction == RIGHT){
    DDRD |= (1<<PD10);
    }
    else{
    DDRD &= ~(1<<PD10);
    }
}

int Motor_SetSpeed(SPEED){
    if (SPEED > 255){
        SPEED = 255;
    }
    if(SPEED < 0){
        SPEED = 0;
    }

ActualSpeed = SPEED;
}

void Motor_setPosition(int xPos){
    


}