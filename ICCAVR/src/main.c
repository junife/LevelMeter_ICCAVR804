#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"
#include "segDisp.h"
#include "led.h"
#include "button.h"
#include "memory.h"
#include "control.h"

//hujunfeng

void main(void)
{
  //u16 ad_val;
  //u8 ad_cnt = 0, cnt = 0;
  //u32 ad_sum = 0;
  //u8 second = 0;

  peripheral_init();         //≥ı ºªØ
  variables_init(); 
  while(1)
  {
    if(timer_100ms_flag)
	{
	  Button_Scan();
	  timer_100ms_flag = FALSE;
	  Con_Monitor();
	  WDR(); //kick watchdog
	}
	
	Con_Monitor();
	
    switch(module_state)
	{
	  case MODULE_STATE_INIT:
	    Con_Module_Init_Proc();
	    break;
		
      case MODULE_STATE_WORK_NORM:
	    Con_Module_Work_Norm_Proc();
	    break;
		
	  case MODULE_STATE_WORK_WARN:
	    Con_Module_Work_Warn_Proc();
	    break;

      case MODULE_STATE_COMMUNICATE:
        Con_Module_Communicate_Proc();
	    break;

      case MODULE_STATE_SERVICE:
	    Con_Module_Service_Proc();
	    break;	
		
	  case MODULE_STATE_ERROR:
	    Con_Module_Error_Proc();
	    break;	
	
	  case MODULE_STATE_QUIT:
	    Con_Module_Quit_Proc();
	    break;	
		
	  default:
	    break;
	}
  
  
  
    //Button_Scan();
	//if(timer_100ms_flag)
	//{
	  //cnt++;
	//}
	
	//ad_val = EEPROM_Read(0x10);
    //Seg_Number_Show(ad_val, 100);
	
	//LedBlink(LED_D1, BLINK_1HZ);
	//LedBlink(LED_D2, BLINK_2HZ);
    //Seg_Number_Show(969, 100);
	//Seg_Alpha_Show(g, o, d, 100);
    //Delay(100);       //—” ±
  }
}


