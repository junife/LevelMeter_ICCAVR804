#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"
#include "segDisp.h"
#include "led.h"
#include "button.h"
#include "memory.h"
#include "control.h"
#include "seg_HC164.h"

static u8  tickCnt = 0;

	
void Con_Module_Init_Proc(void)
{
  ADDR_CODE_T    temp_addr_code;
  MT_FULL_T      temp_mt_full;
  MT_EMPTY_T     temp_mt_empty;
  PER_HIGH_T     temp_per_high;
  PER_LOW_T      temp_per_low;
  RESP_TIME_T    temp_resp_time;
  HV_800V_T      temp_hv_value;
  //EEPROM_Write_Bytes(SEQ_NUM_ADDR, &me_seq_num.year, sizeof(SEQ_NUM_T));
  //EEPROM_Write_Bytes(ADDR_CODE_ADDR, &me_addr_code.highByte, sizeof(ADDR_CODE_T));
  //EEPROM_Write_Bytes(HIGH_THRESH_ADDR, &me_high_thresh.highByte, sizeof(HIGH_THRESH_T));
  //EEPROM_Write_Bytes(LOW_THRESH_ADDR, &me_low_thresh.highByte, sizeof(LOW_THRESH_T));
  //EEPROM_Write_Bytes(OP_TIME_LOW_ADDR, &me_op_time.val[0], sizeof(OP_TIME_T));
	  
  EEPROM_Read_Bytes(ADDR_CODE_ADDR, &temp_addr_code.highByte, sizeof(ADDR_CODE_T));
  EEPROM_Read_Bytes(MT_FULL_ADDR, &temp_mt_full.highByte, sizeof(MT_FULL_T));
  EEPROM_Read_Bytes(MT_EMPTY_ADDR, &temp_mt_empty.highByte, sizeof(MT_EMPTY_T));
  EEPROM_Read_Bytes(PER_HIGH_ADDR, &temp_per_high.highByte, sizeof(PER_HIGH_T));
  EEPROM_Read_Bytes(PER_LOW_ADDR, &temp_per_low.highByte, sizeof(PER_LOW_T));
  EEPROM_Read_Bytes(RESP_TIME_ADDR, &temp_resp_time.highByte, sizeof(RESP_TIME_T));
  EEPROM_Read_Bytes(HV_800V_ADDR, &temp_hv_value.highByte, sizeof(HV_800V_T));
  
  g_addr_code = temp_addr_code.highByte*100 + temp_addr_code.lowByte;
  g_mt_full = temp_mt_full.highByte*100 + temp_mt_full.lowByte;
  g_mt_empty = temp_mt_empty.highByte*100 + temp_mt_empty.lowByte;
  g_per_high = temp_per_high.highByte*100 + temp_per_high.lowByte;
  g_per_low = temp_per_low.highByte*100 + temp_per_low.lowByte;
  g_resp_time = temp_resp_time.highByte*100 + temp_resp_time.lowByte;
  g_hv_value = temp_hv_value.highByte*100 + temp_hv_value.lowByte;
  
  KZ1_OUT_LOW();   
  KZ2_OUT_HIGH(); 
  
  RL1_OPEN();  
  RL2_OPEN();  
  
  if(tickCnt<2)
  {
    if(timer_1000ms_flag)
	{
	  timer_1000ms_flag = FALSE;
	  if(tickCnt%2 == 0)
	  {
	  	Seg_164_Number(g_addr_code, SEG_COLOR_GREEN, MARK_NULL);
		//LedLight(LED_D1, OFF);
	  }
	  else
	  {
		//LedLight(LED_D1, ON);
	  }
	  tickCnt++;
	}
  }
  else if(tickCnt<5)
  {
    if(timer_1000ms_flag)
	{
	  timer_1000ms_flag = FALSE;
	  tickCnt++;
	  Seg_164_Alpha(H, U, g, E, SEG_COLOR_RED);
	  //Seg_164_Number(8888, SEG_COLOR_RED, MARK_NULL);
	}
	LedLight(LED_D1, ON);
	LedLight(LED_D2, ON);
  }
  else
  {
    LedLight(LED_D1, OFF);
    LedLight(LED_D2, OFF);
    module_prevState = MODULE_STATE_INIT;
    module_state = MODULE_STATE_WORK_NORM;
	tickCnt = 0;
  }
}

void Con_Module_Work_Norm_Proc(void)
{
  RL1_CLOSE();
  RL2_CLOSE();
  materialDetect();  //change module state in this function
  
  if(Per_Bypass_Ms(1000) == TRUE)
  {
    buttonDetect();
  }

  if(PORT_KZ1_HIGH_IN() == HIGH)
  {
  }
  else
  {
  }

  if(PORT_KZ2_LOW_IN() == LOW)
  {
  }
  else
  {
  }
}

void Con_Module_Work_Warn_Proc(void)
{
  RL1_OPEN();
  RL2_OPEN();
  materialDetect();  //change module state in this function
  
  if(Per_Bypass_Ms(1000) == TRUE)
  {
    buttonDetect();
  }
}

void Con_Module_Communicate_Proc(void)
{
}

void Con_Module_Service_Proc(void)
{
  if(Per_Bypass_Ms(1000) == TRUE)
  {
    buttonDetect();
  }
}

void Con_Module_Error_Proc(void)
{
}

void Con_Module_Quit_Proc(void)
{
    if((button[1].heldFlag == FALSE)&&(button[0].heldFlag == FALSE))
	{
	    module_state = MODULE_STATE_INIT;
		module_quit_flag = FALSE;
		
		LedBlink(LED_D1, BLINK_2HZ);
	    LedBlink(LED_D2, BLINK_2HZ);
	    Per_Dly_Ms(2000);
	}
}

u8 PORT_KZ1_HIGH_IN(void)    
{ 
    u8 val = (PIND & BIT(3)) >> 3;  //not PORTD, but should use PIND
	if(val == HIGH)
	{
	    return TRUE;
	}
	else
	{
	    return FALSE;
	}
}

u8 PORT_KZ2_LOW_IN(void)    
{   
    u8 val = (PIND & BIT(2)) >> 2;
    if(val == LOW)
	{
	    return TRUE;
	}
	else
	{
	    return FALSE;
	}
}

void getMaxVal(u16 length, u16 inData, u16* maxArray)
{
  u16 i = 0;
  u16 temp = 0;
  for(i=0; i<length; i++)
  {
	if(inData > maxArray[i])
	{ 
	  temp = maxArray[i];
	  maxArray[i] = inData;
	  inData = temp;
	}
  }
}

u32 getAvgVal(u16 length, u16* inArray)
{
  u16 i,j;
  u16 temp = 0;
  u32 inAvg = 0, inSum = 0;
  
  /*for(i=0; i<length; i++)
  {
    for(j=i; j<length-1; j++)
	{
	  if(inArray[j]<inArray[j+1])
	  {
	    temp = inArray[j];
	    inArray[j] = inArray[j+1];
		inArray[j+1] = temp;
	  }
	}
  }*/
  
  for(i=0; i<length; i++)
  {
    inSum += inArray[i];   //original(128-64 =64);  now(128-0=128)
  }
  
  inAvg = inSum;   //inAvg = inSum*128/128;   //inAvg = inSum*2;  //inAvg = inSum*128/64;  min is about 344
  return inAvg;
}


//detect material
void materialDetect(void)
{
  static u32 ad_sum = 0; 
  //static u16 ad_val = 0; 
  static u16 ad_cnt = 0; 
  static u8 temp = 0; 
  static u16 cnt = 0; 
  static u16 maxVal[128] = {0};  //2000/20=100
  //static u16 maxValTwo[128] = {0};
  u16 disp_val = 0; 
  u16 i = 0, ad_temp = 0;
  static u16 iTest = 0;
  static SEG_COLOR_ENUM dispColor = SEG_COLOR_GREEN;
  static s16 prev_val = 0;
  static u16 nThreeSec = 0;
  s16 ad_val = 0, ad_val_one = 0, ad_val_two = 0;
  u32 ad_arr_sum = 0;
  u16 temp_resp_time = 0;
  u32 high_thresh = 0, low_thresh = 0;
  
  if(timer_1ms_flag)
  {
    timer_1ms_flag = FALSE;
	
  	if(PORT_KZ2_LOW_IN() == TRUE)
  	{
  	  if(PORT_KZ1_HIGH_IN()==TRUE) //value is small
  	  {
  	    //ad_temp = adc_start(AD_KZ1)*36 + 258;
		//ad_temp = adc_start(AD_KZ1);  //changed to adc_start(AD_KZ1)+100, 20160124
		ad_temp = adc_start(AD_KZ1) + 100;  //100 is offset
		
		//LedLight(LED_D2, ON);
		
  	    getMaxVal(128, ad_temp, (u16*)&maxVal);
  	  }
  	  else  //HIGH_IN is low, means value is big 
  	  {
  	    //ad_temp = adc_start(AD_KZ1)*54 + 258;     //(*3/2)*36
  		//getMaxVal(128, ad_temp, (u16*)&maxValOne);
		
		//LedLight(LED_D2, OFF);
  	  }
  	}
	
  	/*for(i=0; i<32; i++)
  	{
  	maxValOne[i] = i;
  	maxValTwo[i] = 2*i;
  	}*/
  	
  	cnt += 1;
  	if(cnt >= 3000) //3000ms/20ms = 150 times
  	{	
  	  cnt = 0; 
  	  ad_arr[nThreeSec] = getAvgVal(128, (u16*)&maxVal); 
	  temp_resp_time = g_resp_time/3;
	  
	  if((nThreeSec<150) && (nThreeSec < temp_resp_time))   //3s*150=450
	  {
	    nThreeSec++;
	  }
	  else
	  {
	    nThreeSec = 0;
	  }  
	  
	  for(i=0; i<temp_resp_time; i++)
	  {
	    ad_arr_sum += ad_arr[i];
	  }
	  
	  //Seg_164_Number(ad_arr_sum, dispColor, MARK_NULL);
	  
	  ad_val = ad_arr_sum/temp_resp_time;
	  ad_arr_sum = 0;
	  //Seg_164_Number(ad_val, dispColor, MARK_NULL);
	  
  	  /*if(ad_val_one > ad_val_two)
  	  {
  	    ad_val = ad_val_one;
  		LedLight(LED_D1, OFF);
  	  }
  	  else
  	  {
  	    ad_val = ad_val_two;
  		LedLight(LED_D1, ON);
  	  }*/
  	   
  	  if(prev_val < 10)
  	  {
  	      prev_val = ad_val;  //the first time
  	  }
  	  else if(prev_val - ad_val > 1000)  //C编译器有问题，u16 - u16 结果如果为负，会被转成正数
  	  {
  	    ad_val = prev_val - 1000;
  	  }	
  	  else if(prev_val - ad_val > 100)
  	  {
  	    ad_val = prev_val - 100;
  	  }
  	  else if(prev_val - ad_val > 10)
  	  {
  	    ad_val = prev_val - 10;
  	  }
  	  else if(ad_val - prev_val > 1000)
  	  {
  	    ad_val = prev_val + 1000;
  	  }
  	  else if(ad_val - prev_val > 100)
  	  {
  	    ad_val = prev_val + 100;
  	  }
  	  else if(ad_val - prev_val > 10)
  	  {
  	  	ad_val = prev_val + 10;
  	  }
  	  
  	  high_thresh = g_mt_empty + (g_mt_full - g_mt_empty)*g_per_high/100;
	  low_thresh = g_mt_empty +(g_mt_full - g_mt_empty)*g_per_low/100;

  	  if(ad_val < low_thresh)
  	  {
        dispColor = SEG_COLOR_GREEN;
  		module_state = MODULE_STATE_WORK_NORM;
  	  }
  	  else if(ad_val > high_thresh)
  	  {
        dispColor = SEG_COLOR_RED;
        module_state = MODULE_STATE_WORK_WARN;
  	  }
  	  
	  	//LedLight(LED_D1, ON);
        //LedLight(LED_D2, OFF);
		//Per_Dly_Ms(5000);
		
  	  Seg_164_Number(ad_val, dispColor, MARK_NULL);
  	  
  	  prev_val = ad_val;
  	  
  	  for(i=0; i<128; i++)
  	  {
  	    maxVal[i] = 0;
  	  }
  	  
  	  temp++;
  	  if(temp < 5)
  	  {
  	     //temp = 0;
  		 //Seg_164_Number(ad_val_one, dispColor, MARK_NULL);
  		 //LedLight(LED_D2, ON);
  	  }
  	  else 
  	  {
  	     //if(temp > 10) temp = 0;
  		 //Seg_164_Number(ad_val_two, dispColor, MARK_NULL);
  		 //LedLight(LED_D2, OFF);
  	  }
    }
  }
}
  
  
void buttonDetect(void)
{
  static SERV_STATE_ENUM serv_state = SERV_STATE_MIN;
  static SERV_STATE_ENUM serv_prevState = SERV_STATE_MIN;
  u8 temp_disp_code = 0;

  if(module_quit_flag == TRUE)
  {
  	module_state = MODULE_STATE_QUIT;
	serv_state = SERV_STATE_MIN;;
	return;
  }
  
  if((button[1].heldFlag == TRUE)&&(button[0].heldFlag == TRUE))
  {
    button[1].heldFlag = FALSE;
	button[0].heldFlag = FALSE;

	module_state = MODULE_STATE_SERVICE;
    serv_state = SERV_STATE_RESET;
  }
  else if((button[1].heldFlag == TRUE) && (button[0].pressedFlag == FALSE))
  {
    button[1].heldFlag = FALSE;
	module_state = MODULE_STATE_SERVICE;
    serv_state = SERV_STATE_CODE_CHANGE;
	//LedLight(LED_D2, ON);
	//LedLight(LED_D1, OFF);
  }
  else if((button[0].heldFlag == TRUE) && (button[1].pressedFlag == FALSE))
  {
    button[0].heldFlag = FALSE;
	module_state = MODULE_STATE_SERVICE;
    serv_state = SERV_STATE_PARA_CHANGE;
	//LedLight(LED_D1, ON);
	//LedLight(LED_D2, OFF);
  }
  else if(button[1].releasedFlag == TRUE)
  {
    button[1].releasedFlag = FALSE;   //JP2
	  timer_3s_cnt = 0;
    timer_3s_flag = FALSE;
	  module_prevState = module_state;
    module_state = MODULE_STATE_SERVICE;
	  g_disp_code++;
  	if((g_disp_code >= DISP_CODE_MAX) || (g_disp_code <= DISP_CODE_MIN))
  	{
  	  g_disp_code = DISP_CODE_0;
  	}
    serv_state = SERV_STATE_DISP_CODE;   //JP2
  }
  else if(button[0].releasedFlag == TRUE)
  {
    button[0].releasedFlag = FALSE;   //JP1
    timer_3s_cnt = 0;
    timer_3s_flag = FALSE;

	module_state = MODULE_STATE_SERVICE;
	if(serv_prevState == SERV_STATE_PARA_CHANGE)
	{
	  //LedLight(LED_D2, ON);
	  //LedLight(LED_D1, OFF);
	  serv_state = SERV_STATE_PARA_SAVE;   //JP1
	}
	else
	{ //LedLight(LED_D1, ON);
	  //LedLight(LED_D2, OFF);
	  serv_state = SERV_STATE_DISP_PARA;   //JP1
	}
  }
  else
  {
    //serv_state = SERV_STATE_MIN; 
	//timer_3s_cnt = 0;
    //timer_3s_flag = FALSE;
	LedLight(LED_D2, OFF);
	//LedLight(LED_D1, OFF);
	//Per_Dly_Ms(2000);
  }

  switch(serv_state)
  {
    case SERV_STATE_RESET:
      me_mt_full.highByte = MT_FULL/100;
      me_mt_full.lowByte = MT_FULL%100;
      EEPROM_Write_Bytes(MT_FULL_ADDR, &me_mt_full.highByte, 2);
      me_mt_empty.highByte = MT_EMPTY/100;
      me_mt_empty.lowByte = MT_EMPTY%100;
      EEPROM_Write_Bytes(MT_EMPTY_ADDR, &me_mt_empty.highByte, 2);
	  
	  me_per_high.highByte = PER_HIGH/100;
      me_per_high.lowByte = PER_HIGH%100;
      EEPROM_Write_Bytes(PER_HIGH_ADDR, &me_per_high.highByte, 2);
      me_per_low.highByte = PER_LOW/100;
      me_per_low.lowByte = PER_LOW%100;
      EEPROM_Write_Bytes(PER_LOW_ADDR, &me_per_low.highByte, 2);
	  
	  me_resp_time.highByte = RESP_TIME_VALUE/100;
      me_resp_time.lowByte = RESP_TIME_VALUE%100;
      EEPROM_Write_Bytes(RESP_TIME_ADDR, &me_resp_time.highByte, 2);
	  
      me_hv_value.highByte = HV_800V_VALUE/100;
      me_hv_value.lowByte = HV_800V_VALUE%100;
      EEPROM_Write_Bytes(HV_800V_ADDR, &me_hv_value.highByte, 2);
	  
	  me_addr_code.highByte = ADDR_CODE_VALUE/100;
	  me_addr_code.lowByte = ADDR_CODE_VALUE%100;
	  EEPROM_Write_Bytes(ADDR_CODE_ADDR, &me_addr_code.highByte, 2);
	  
	  serv_state = SERV_STATE_MIN;
	  module_quit_flag = TRUE;
      break;
  
    case SERV_STATE_DISP_CODE:	
      if(timer_3s_cnt == 0) 
      {
        timer_3s_cnt++;
      }
      if(timer_3s_flag == TRUE)
      {
        timer_3s_flag = FALSE;
        timer_3s_cnt = 0;
        serv_state = SERV_STATE_DISP_PARA;
      }
      temp_disp_code = g_disp_code - 1;
      Seg_164_Number(temp_disp_code, SEG_COLOR_GREEN, MARK_NULL);
      break;
	  
    case SERV_STATE_CODE_CHANGE:	 
      g_disp_code++;
      if((g_disp_code >= DISP_CODE_MAX) || (g_disp_code <= DISP_CODE_MIN))
      {
        g_disp_code = DISP_CODE_0;
      }
	
	  temp_disp_code = g_disp_code - 1;
      Seg_164_Number(temp_disp_code, SEG_COLOR_GREEN, MARK_NULL);
      break;
  
    case SERV_STATE_DISP_PARA:	
	  switch(g_disp_code)
      {
        case DISP_CODE_0: 
		  g_disp_para = 0;
	      if(timer_3s_cnt == 0) 
          {
            timer_3s_cnt++;
          }
          if(timer_3s_flag == TRUE)
          {
            timer_3s_flag = FALSE;
            timer_3s_cnt = 0;
		    module_state = MODULE_STATE_WORK_NORM;
            serv_state = SERV_STATE_MIN;
          }
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
        
        case DISP_CODE_1:
		  g_disp_para = g_mt_full;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
      
        case DISP_CODE_2:	  
		  g_disp_para = g_mt_empty;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
      
        //case DISP_CODE_12:	
		  //g_disp_para = g_hv_value;
		  //timer_3s_cnt = 0;
          //break;
		  
        case DISP_CODE_3:	
		  g_disp_para = g_per_high;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_HIGH);
		  break;
		  
	    case DISP_CODE_4:	
		  g_disp_para = g_per_low;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_LOW);
		  break;
		  
		  
        case DISP_CODE_5:	 
		  g_disp_para = g_resp_time;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
        case DISP_CODE_6:	 
		  g_disp_para = g_resp_time;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
		case DISP_CODE_7:	 
		  g_disp_para = g_addr_code;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
        case DISP_CODE_8:	 
		  g_disp_para = g_addr_code;
		  timer_3s_cnt = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
        default:
		  timer_3s_cnt = 0;
          break;
      }

      break;
    
    case SERV_STATE_PARA_CHANGE:	 
	  switch(g_disp_code)
      {
        case DISP_CODE_0: 
	      g_disp_para = 0;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
        
        case DISP_CODE_1:
		  g_disp_para += 10;
          if((g_disp_para >= DISP_PARA_MAX) || (g_disp_para <= DISP_PARA_MIN))
          {
            g_disp_para = DISP_PARA_MIN;
          }
		  if(g_disp_para <= g_mt_empty)
		  {
		    LedLight(LED_D1, ON);
		  }
		  else
		  {
		    LedLight(LED_D1, OFF);
		  }
          g_mt_full = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
      
        case DISP_CODE_2:	  
		  g_disp_para += 10;
          if((g_disp_para >= DISP_PARA_MAX) || (g_disp_para <= DISP_PARA_MIN))
          {
            g_disp_para = DISP_PARA_MIN;
			LedLight(LED_D1, ON);
          }
		  
		  if(g_disp_para >= g_mt_full)
		  {
		    LedLight(LED_D1, ON);
		  }
		  else
		  {
		    LedLight(LED_D1, OFF);
		  }
          g_mt_empty = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
      
        //case DISP_CODE_12:	
          //g_hv_value = g_disp_para;
          //break;
		  
        case DISP_CODE_3:
          g_disp_para += 5;
          if(g_disp_para > 100)
          {
            g_disp_para = 0;
          }
		  if(g_disp_para <= g_per_low)
		  {
		    LedLight(LED_D1, ON);
		  }
		  else
		  {
		    LedLight(LED_D1, OFF);
		  }
          g_per_high = g_disp_para;	
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_HIGH);
		  break;
		  
	    case DISP_CODE_4:	
		  g_disp_para += 5;
          if(g_disp_para > 100)
          {
            g_disp_para = 0;
          }
		  if(g_disp_para >= g_per_high)
		  {
		    LedLight(LED_D1, ON);
		  }
		  else
		  {
		    LedLight(LED_D1, OFF);
		  }
          g_per_low = g_disp_para;	
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_LOW);
		  break;
		
        case DISP_CODE_5:	 
		  g_disp_para += 1;
          if(g_disp_para > 450) 
          {
            g_disp_para = 3;
          }
          g_resp_time = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
        case DISP_CODE_6:	 
		  g_disp_para -= 1;
          if(g_disp_para < 3)
          {
            g_disp_para = 450;
          }
          g_resp_time = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;   
		  
	    case DISP_CODE_7:	 
		  g_disp_para += 1;
          if((g_disp_para > 9999) || (g_disp_para < 1000))
          {
            g_disp_para = 1000;
          }
          g_addr_code = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;
		  
        case DISP_CODE_8:	 
		  g_disp_para -= 1;
          if((g_disp_para > 9999) || (g_disp_para < 1000))
          {
            g_disp_para = 9999;
          }
          g_addr_code = g_disp_para;
		  Seg_164_Number(g_disp_para, SEG_COLOR_GREEN, MARK_NULL);
          break;  
		  
        default:
          break;
      }
	  serv_prevState = serv_state;
	  serv_state = SERV_STATE_MIN;
      break;

    case SERV_STATE_PARA_SAVE:	
	  if(g_mt_full <= g_mt_empty)
	  {
	    g_mt_full = g_mt_empty;
		if(g_mt_empty > 400)
		{
		  g_mt_empty -= 100;
		}
		else
		{
		  g_mt_full += 100;
		}
	  }  
	  
	  if(g_per_high <= g_per_low)
	  {
	    g_per_high = g_per_low;
		if(g_per_low > 50)
		{
		  g_per_low -= 10;
		}
		else
		{
		  g_per_high += 10;
		}
	  }  
	  
	  if(timer_3s_cnt == 0) 
      {
        timer_3s_cnt++;
      }
      if(timer_3s_flag == TRUE)
      {
        timer_3s_flag = FALSE;
        timer_3s_cnt = 0;
		me_mt_full.highByte = g_mt_full/100;
        me_mt_full.lowByte = g_mt_full%100;
        EEPROM_Write_Bytes(MT_FULL_ADDR, &me_mt_full.highByte, 2);
        me_mt_empty.highByte = g_mt_empty/100;
        me_mt_empty.lowByte = g_mt_empty%100;
        EEPROM_Write_Bytes(MT_EMPTY_ADDR, &me_mt_empty.highByte, 2);
		
		me_per_high.highByte = g_per_high/100;
        me_per_high.lowByte = g_per_high%100;
        EEPROM_Write_Bytes(PER_HIGH_ADDR, &me_per_high.highByte, 2);
        me_per_low.highByte = g_per_low/100;
        me_per_low.lowByte = g_per_low%100;
        EEPROM_Write_Bytes(PER_LOW_ADDR, &me_per_low.highByte, 2);	
		
		me_resp_time.highByte = g_resp_time/100;
        me_resp_time.lowByte = g_resp_time%100;
        EEPROM_Write_Bytes(RESP_TIME_ADDR, &me_resp_time.highByte, 2);
		
        me_hv_value.highByte = g_hv_value/100;
        me_hv_value.lowByte = g_hv_value%100;
        EEPROM_Write_Bytes(HV_800V_ADDR, &me_hv_value.highByte, 2);
		
		me_addr_code.highByte = g_addr_code/100;
        me_addr_code.lowByte = g_addr_code%100;
        EEPROM_Write_Bytes(ADDR_CODE_ADDR, &me_addr_code.highByte, 2);
        LedLight(LED_D1, ON);
        LedLight(LED_D2, ON);
	    serv_state = SERV_STATE_MIN;
      }
      break;

    default:
      break;
  }  
}

void Con_Monitor(void)
{
  if(FG_IO_IN() == HIGH)
  {
    LedBlink(LED_D1, BLINK_1HZ);
  }  
  else
  {
    LedLight(LED_D1, OFF);
  }
}
  
//burn software don't erase the EEPROM