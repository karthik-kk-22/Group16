#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGCUART_R |= (1<<2);  // UART2 clock
    SYSCTL_RCGCGPIO_R |= (1<<3);  // Port D clock

    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R  |= (1<<7);
    GPIO_PORTD_AFSEL_R |= (1<<6) | (1<<7);
    GPIO_PORTD_DEN_R   |= (1<<6) | (1<<7);
    GPIO_PORTD_PCTL_R &= ~((0xF<<24) | (0xF<<28));
    GPIO_PORTD_PCTL_R |=  (0x1<<24) | (0x1<<28);

    UART2_CTL_R &= ~UART_CTL_UARTEN;
    UART2_IBRD_R = 104;
    UART2_FBRD_R = 11;
    UART2_LCRH_R = 0x60;
    UART2_CC_R   = 0x00;

    UART2_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE;

    while(1)
    {
        while(UART2_FR_R & (1<<5));
        UART2_DR_R = 0x55;
    }
}
