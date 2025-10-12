#include<stdio.h>
#include<stdint.h>
#include<tm4c123gh6pm.h>

struct
{
    uint32_t u;     // 32-bit IEEE format computed by fadd
    float f;        // reference result computed by c = a + b
} buf[0x100];
int index;


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


void fadd_test(float a, float b)
{
    union
    {
        uint32_t u;     // access as 32-bit raw bits
        float f;        // access as a floating-point number
    } A, B, C;

    float c;

    A.f = a;
    B.f = b;

    C.u = fadd(A.u, B.u);       // output of asm code
    c = a + b;                  // reference output by C code

    if (index < 0x100)
    {
        buf[index].u = C.u;     // asm result
        buf[index].f = c;       // C result
        index++;
    }

    return;
}

int main(void)
{
    fadd_test(100.0f, 0.25f);       // 100.25f  (0x42C88000)
    fadd_test(1.5f, 1.5f);          // 3.0f     (0x40400000)
    fadd_test(2.75f, 1.5f);         // 4.25f    (0x40880000)
    fadd_test(1024.0f, 1.0f);       // 1025.0f  (0x44802000)
    fadd_test(1.0f, 0.125f);        // 1.125f   (0x3F900000)
    fadd_test(65536.0f, 256.0f);    // 65792.0f (0x47808000)

    while (1);

    return 0;
}
