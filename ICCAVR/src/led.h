#ifndef LED_H
#define LED_H 
#include  "variables.h"

#define  LED_D1           1
#define  LED_D2           2
#define  BLINK_1HZ        1
#define  BLINK_2HZ        2

void LedBlink(u8 Num, u8 Freq);
void LedLight(u8 Num, u8 Action);

#endif