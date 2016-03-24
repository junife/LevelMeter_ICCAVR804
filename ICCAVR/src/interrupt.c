#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"

#pragma interrupt_handler timer0_ovf_isr:iv_TIM0_OVF
void timer0_ovf_isr(void)   //1ms
{
  static u8 timer_100ms_cnt = 0, timer_1000ms_cnt = 0;
  
  //TCNT0 = 0x00 /*INVALID SETTING*/; //reload counter value
  TCNT0=131; 	 //ÖØÐÂ¸³³õÖµ
  
  timer_1ms_flag = TRUE;
  
  if(timer_100ms_cnt++ == 100)
  {
     timer_100ms_cnt = 0;
	 timer_100ms_flag = TRUE;
	 if(timer_1000ms_cnt++ == 10)
	 {
	   timer_1000ms_cnt = 0;
	   timer_1000ms_flag = TRUE;
	 }
	 
	 if(timer_3s_cnt > 0)
	 {
	   timer_3s_cnt++;
	 }
	 if(timer_3s_cnt == 30)
	 {
	   timer_3s_cnt = 0;
	   timer_3s_flag = TRUE;
	 }
  }
  
  per_dly_1ms_cnt++;
  
  if(per_bypass_1ms_cnt > 0)
  {
    per_bypass_1ms_cnt++;
  }
  
  //if(led_500ms_start_flag)
  //{
    led_500ms_cnt++;
  //}
  //else
  //{
    //led_500ms_cnt = 0;
  //}
  
  //if(led_250ms_start_flag)
  //{
    led_250ms_cnt++;
  //}
  //else
  //{
    //led_250ms_cnt = 0;
  //}
}


//#pragma interrupt_handler timer1_ovf_isr:iv_TIM1_OVF
#pragma interrupt_handler timer1_ovf_isr:iv_TIM1_OVF
void timer1_ovf_isr(void)   //100ms
{
  static u8 i = 0;
  //TIMER1 has overflowed
  TCNT1H = 0xCF;   //100ms/8us = 12500, 65536-12500 = 0xCF2C
  TCNT1L = 0x2C;
  
  i++;
  if(i==10)
  {
     i = 0;
  }
}
