#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void){
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
        GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
        GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
        GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
        GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
        GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP

        GPIO_PORTF_DATA_R = 0x0;             // LED OFF

        int delay = 200000;
        int lpress=0;
        int i=0;
         while (1){
             if ((GPIO_PORTF_DATA_R & 0x01)==0 && (lpress == 0) ){
                 lpress = 1;
                 GPIO_PORTF_DATA_R = i;
                 i=i+2;
                 if(i>14){
                     i=0;
                 }
             }
             int x=0;
             while(x<delay){
                 x++;
             }
             if ((GPIO_PORTF_DATA_R & 0x01) !=0){
                 lpress=0;
             }
         }
         return 0;
}
