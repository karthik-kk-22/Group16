#include "uart_ee627.h"
#include <stdint.h>

int main(void)
{
    UART_setup();  // Initialize UART4

    while (1)
    {   int i;
        UART_send(0x55);
        for (i = 0; i < 1000000; i++);
        UART_send(0xAA);
        for (i = 0; i < 1000000; i++);
    }
}
