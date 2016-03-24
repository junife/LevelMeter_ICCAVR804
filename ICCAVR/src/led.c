#include "iom16v.h"
#include <macros.h>			//包含"位"操作头文件
#include "led.h"
#include "variables.h"	
#include "segDisp.h"	

#define  LED_D1_ON       PORTB &= ~(1<<1)
#define  LED_D1_OFF      PORTB |= (1<<1)

#define  LED_D2_ON       PORTB &= ~(1<<2)
#define  LED_D2_OFF      PORTB |= (1<<2)

void LedLight(u8 Num, u8 Action)
{
  if(Action == ON)
  {
    if(Num == LED_D1)
    {
	  //PORTB |= BIT(1);
	  LED_D1_ON;
	}
	else if(Num == LED_D2)
	{
	  //PORTB |= BIT(2);
	  LED_D2_ON;
	}
	else
	{
	}
  }
  else  //action == OFF
  {
    if(Num == LED_D1)
    {
	  //PORTB &= ~BIT(1);
	  LED_D1_OFF;
	  
	}
	else if(Num == LED_D2)
	{
	  //PORTB &= ~BIT(2);
	  LED_D2_OFF;
	}
	else
	{
	}
  }
  
  //led_500ms_start_flag = FALSE;
  //led_500ms_cnt = 0;
  //led_250ms_start_flag = FALSE;
  //led_250ms_cnt = 0;
  
}

void LedBlink(u8 Num, u8 Freq)
{
  static u8 i = 0;
  switch(Freq)
  {
    case BLINK_1HZ:
	  //led_500ms_start_flag = TRUE;
	  if(led_500ms_cnt > 500)
	  {
	    led_500ms_cnt = 0;
		if(Num == LED_D1)
		{
		  PORTB ^= BIT(1);
		}
		else if(Num == LED_D2)
		{
		  PORTB ^= BIT(2);
		}
		else
		{
		}
      }
	  break;
	
    case BLINK_2HZ:
	  //led_250ms_start_flag = TRUE;
	  if(led_250ms_cnt > 250)
	  {
	    led_250ms_cnt = 0;
		if(Num == LED_D1)
		{
		  PORTB ^= BIT(1);
		}
		else if(Num == LED_D2)
		{
		  PORTB ^= BIT(2);
		}
		else
		{
		}
      }
	  break;
	  
	default:
	  break;
  }
}

