#include<stdio.h>
#include<stdint.h>
#include<tm4c123gh6pm.h>


uint32_t fadd(uint32_t p, uint32_t q){
    uint32_t exp1,exp2;
    uint32_t man1,man2;
    uint32_t e;

    exp1 = (p>>23) & 0xFF;
    exp2 = (q>>23) & 0xFF;

    man1 = p & (0x7FFFFF);
    man2 = q & (0x7FFFFF);

    man1 = man1 | 0x800000;
        man2 = man2 | 0x800000;

    if(exp1 == exp2){
        e = exp1;
    }

    if (exp1 > exp2){
        int shift;
        shift = exp1-exp2;
        man2 = (man2 >> shift);
        e = exp1;
    }
    if (exp1 < exp2){
        int shift;
        shift = exp2 - exp1;
        man1 = (man1 >> shift);
        e = exp2;
    }


    uint32_t sum = man1+man2;

    if (sum & (0x1000000)){
        sum = sum>>1;
        e=e+1;
    }

    sum = sum & (0x7FFFFF);

    uint32_t result;
    result = (e<<23) | sum;
    return result;
}

int main(void)
{
    uint32_t p,q,r;
    p= 0x41C80000;  /// 25 in decimal
    q= 0x3dcccccd;  /// 0.1 in decimal
    r = fadd(p,q);
    while (1);

    return 0;
}
