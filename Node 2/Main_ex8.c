
#include "sam.h"
#include "printf_stdarg.h"
#include "uart.h"
#include "can_controller.h"
#include "can_interrupt.h"


int main(void)
{	
    /* Initialize the SAM system */ 
    SystemInit();
	CAN_MESSAGE rex_mess;
	
	configure_uart();
	
	can_init_def_tx_rx_mb(0x290561);
    uint8_t x,y;
    uint8_t x_DAC
	
	while (1) 
    {
		x=can_receive(&rex_mess,2);
		y=can_receive(&rex_mess,1);

        x_DAC=JoyToDAC(x);
        SendToDAC(x_DAC)
        //convert X to DAC
        //send to DAC

	}
}


}

int JoyToDAC(int JoyPos){

}
int SendToDAC(int Data){


}