#ifndef PERIPHERAL_H
#define PERIPHERAL_H 

#include "variables.h"

#define  AD0   0
#define  AD1   1
#define  AD2   2

void Delay(signed int cnt);
void peripheral_init(void);
u16 adc_start(u8 Num);
void Per_Dly_Ms(signed int msCnt);
BOOL Per_Bypass_Ms(signed int msCnt);

#endif