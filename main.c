#include <stdint.h>
#include "tm4c123gh6pm.h"

#define TAEN    (1<<0)
#define TAAMS   (1<<3)
#define TAPWML  (1<<6)

void delay(void) {
    int i;
    for (i = 0; i < 500000; i++);
}

int main(void)
{
    // Enable Port F for switches
    SYSCTL_RCGC2_R |= 0x20;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x11;          // PF0, PF4
    GPIO_PORTF_DIR_R &= ~0x11;       // inputs
    GPIO_PORTF_DEN_R |= 0x11;        // digital enable
    GPIO_PORTF_PUR_R |= 0x11;        // pull-ups

    // Enable Wide Timer 0 and Port C
    SYSCTL_RCGCWTIMER_R |= (1<<0);
    SYSCTL_RCGC2_R |= (1<<2);

    // Configure PC4 for WT0CCP0
    GPIO_PORTC_AFSEL_R |= (1<<4);
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFFF0FFFF) | (7<<16);
    GPIO_PORTC_DEN_R |= (1<<4);
    GPIO_PORTC_DIR_R |= (1<<4);

    // Configure Wide Timer 0A for PWM
    WTIMER0_CTL_R &= ~TAEN;           // Disable Timer A
    WTIMER0_CFG_R = 0x04;              // 32-bit mode
    WTIMER0_TAMR_R = 0x0A;            // PWM mode
    WTIMER0_CTL_R &= ~TAPWML;         // Non-inverted PWM
    WTIMER0_TAPR_R = 0;               // No prescaler
    WTIMER0_TAILR_R = 319;            // 50 kHz
    WTIMER0_TAMATCHR_R = 159;         // 50% duty
    WTIMER0_CTL_R |= TAEN;            // Enable Timer A

    while(1)
    {
        if ((GPIO_PORTF_DATA_R & 0x01) == 0) {  // SW2 pressed
            WTIMER0_TAMATCHR_R += 16;
            if (WTIMER0_TAMATCHR_R > WTIMER0_TAILR_R - 16)
                WTIMER0_TAMATCHR_R = WTIMER0_TAILR_R - 16;
            delay();
        }
        if ((GPIO_PORTF_DATA_R & 0x10) == 0) {  // SW1 pressed
            if (WTIMER0_TAMATCHR_R > 16)
                WTIMER0_TAMATCHR_R -= 16;
            delay();
        }
    }
}