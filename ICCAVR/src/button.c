/*****************************************************************
******************************************************************/
#include <iom16v.h>
#include <macros.h>
#include "button.h"
#include "led.h"

BUTTON_STRUCT_T  button[2] = {BUTTON_STATE_UNDEFINED, BUTTON_STATE_UNDEFINED, 0, 0, FALSE, FALSE, FALSE};

void Button_Scan(void)   //button scan, 100ms time_tick
{ 
  static u16 held_time_interval = 0;
  u8 key=0;
  u8 i=0;
  
  DDRC |= 0x03;   //C0, C1 as input
  PORTC |= 0x03;  //add pull_up
  Delay(10);
  key = PINC;
  key = ~key; //low level change to high level

  switch(key&0x03)
  {
    case 0x00:
    	button[0].value = (button[0].value<<1 | 0) & 0x03;  //JP1
    	button[1].value = (button[1].value<<1 | 0) & 0x03;  //JP2
  		break;
    case 0x01: 
        button[0].value = (button[0].value<<1 | 1) & 0x03;
    	button[1].value = (button[1].value<<1 | 0) & 0x03;
	    break;
    case 0x02:
        button[0].value = (button[0].value<<1 | 0) & 0x03;
    	button[1].value = (button[1].value<<1 | 1) & 0x03;
	    break;
	case 0x03:
        button[0].value = (button[0].value<<1 | 1) & 0x03;
    	button[1].value = (button[1].value<<1 | 1) & 0x03;
	    break;
    default:	
      break;
  }    	 
   
  for(i=0; i<2; i++)
  {
  	button[i].prevState = button[i].state;
  	switch(button[i].value)
  	{
  		case 0x00:
  			button[i].state = BUTTON_STATE_NOT_PRESSED;
			button[i].pressedFlag = FALSE;
			//button[i].releasedFlag = FALSE;
			button[i].holdTime = 0;
  			button[i].heldFlag = FALSE;
  			break;
  			
  		case 0x01:
  			button[i].state = BUTTON_STATE_PRESSED;
			button[i].pressedFlag = TRUE;
			button[i].releasedFlag = FALSE;
			button[i].heldFlag = FALSE;
			if(i==0)
			{
			  //LedLight(LED_D1, ON);
			}
			
			if(i==1)
			{
			  //LedLight(LED_D2, ON);
			}
  			break;
  		
  		case 0x02:
  			button[i].state = BUTTON_STATE_RELEASED;
			button[i].releasedFlag = TRUE;
			button[i].pressedFlag = FALSE;
			button[i].heldFlag = FALSE;
			
			if(i==0)
			{
			  //LedLight(LED_D1, OFF);
			}
			
			if(i==1)
			{
			  //LedLight(LED_D2, OFF);
			}
  			break;
  			
  		case 0x03:
  			button[i].state = BUTTON_STATE_HELD;
			button[i].releasedFlag = FALSE;
  			button[i].holdTime++;	
			
  			if(button[i].holdTime > HOLD_TIME_3S)
  			{
  				button[i].heldFlag = TRUE;
				button[i].pressedFlag = FALSE;
				held_time_interval = HOLD_TIME_3S - HOLD_TIME_0_5S;
				//if(held_time_interval < HOLD_TIME_3S - HOLD_TIME_0_1S ) //100ms
				//{
				  //held_time_interval++; //at last it would fatest to 100ms
				//}
				button[i].holdTime = held_time_interval;
				
				if(i==0)
				{
					//LedBlink(LED_D1, BLINK_2HZ);
					//LedLight(LED_D1, ON);
					//LedLight(LED_D2, OFF);
				}
				
				if(i==1)
				{
					//LedLight(LED_D2, ON);
					//LedLight(LED_D1, OFF);
				}
  			}
  			break;
  			
  	  default:
  	  	break;
    }	
  }  
}
