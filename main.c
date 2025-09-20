#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define RED_LED   (1<<1)
#define BLUE_LED  (1<<2)
#define SW1       (1<<4)
#define SW2       (1<<0)

void GPIOF_Handler(void){
    int i;
    GPIO_PORTF_ICR_R |= 1;
    GPIO_PORTF_DATA_R |= BLUE_LED;
    for (i = 0; i < 640000; i++) {
        ;
    }
    GPIO_PORTF_DATA_R &= ~BLUE_LED;
}


int main(void){
    SYSCTL_RCGC2_R |= 0x20;          // enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;  // unlock PF0
    GPIO_PORTF_CR_R   = 0x1F;        // allow changes on PF0–PF4
    GPIO_PORTF_DEN_R  = 0x1F;        // enable digital for PF0–PF4
    GPIO_PORTF_DIR_R  = (RED_LED | BLUE_LED); // LEDs output, switches input
    GPIO_PORTF_PUR_R  = (SW1 | SW2); // pull-up on switches
    GPIO_PORTF_DATA_R = 0x00;        // all off initially

      GPIO_PORTF_IM_R = 0;
      GPIO_PORTF_IS_R = 0;
      GPIO_PORTF_IEV_R =1;
      GPIO_PORTF_ICR_R=1;
      GPIO_PORTF_IM_R = 1;

    NVIC_EN0_R |= (1<<30);

    while(1){

    }
}
