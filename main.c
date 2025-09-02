#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define red_led (1<<1)
#define blue_led (1<<2)
#define green_led (1<<3)

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_DIR_R = 0X0E;
    GPIO_PORTF_PUR_R = 0x11;

    GPIO_PORTF_DATA_R = 0x00;

    while(1){

        if((GPIO_PORTF_DATA_R & 0x11) == 0x10){
            GPIO_PORTF_DATA_R |= red_led;
        }
        else if ((GPIO_PORTF_DATA_R & 0x11)==0x01){
            GPIO_PORTF_DATA_R |= blue_led;
        }
        else if ((GPIO_PORTF_DATA_R & 0x11) == 0x00){
            GPIO_PORTF_DATA_R |= green_led;
        }
        else{
            GPIO_PORTF_DATA_R = 0x00;
        }
    }

	return 0;
}
