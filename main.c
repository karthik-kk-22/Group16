#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define stctrl  (*((volatile uint32_t *)0xE000E010))
#define streload  (*((volatile uint32_t *)0xE000E014))
#define stcurrent  (*((volatile uint32_t *)0xE000E018))

#define enable 1
#define clk_source (1<<2)
#define count (1<<16)
#define red_led (1<<1)
#define blue_led (1<<2)
#define sw_1 (1<<4)

int main(void){

    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_DIR_R = 0X0E;
    GPIO_PORTF_PUR_R = 0X11;
    streload = 0xFFFFFF;
    stctrl |= clk_source;
    GPIO_PORTF_DATA_R = 0x0;

    while(1){
        toggle_blue();
       stctrl |= enable;
       while ((stctrl & count) == 0);
        GPIO_PORTF_DATA_R ^= red_led;
        //// disable timer
        stctrl &= ~enable;
        stcurrent = 0x0;

    }
}

void toggle_blue(void){
    if((GPIO_PORTF_DATA_R & sw_1 ) == 0x00){
        GPIO_PORTF_DATA_R |= blue_led;
    }
    else {
        GPIO_PORTF_DATA_R &= ~blue_led;
    }
}

