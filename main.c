#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

/**
 * main.c
 */

int series_sum(int k){
    volatile int arr[10];
    int i=0;
    for (i=0;i<10;i++){
        arr[i]=i;
    }
    if (k<=1){
        return 1;
    }
    else{
        return k+series_sum(k-1);
    }
}

int main(void)
{   int a = 6;
    int sum = series_sum(a);
    while(1);
	return 0;
}
