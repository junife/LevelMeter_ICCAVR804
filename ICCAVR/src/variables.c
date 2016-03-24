#include  "variables.h"

//BOOL  led_500ms_start_flag;
//BOOL  led_250ms_start_flag;
u16   led_500ms_cnt;
u16   led_250ms_cnt;
u16   per_dly_1ms_cnt;
u16   per_bypass_1ms_cnt;
BOOL  timer_1ms_flag;
BOOL  timer_100ms_flag;
BOOL  timer_1000ms_flag;
u16   g_addr_code; 
u16   g_mt_full;
u16   g_mt_empty;
u16   g_per_high;
u16   g_per_low;
u16   g_resp_time;
u16   g_hv_value;
DISP_CODE_ENUM g_disp_code;
u16   g_disp_para;
u8    eeprom_buf[16] = {0};
u16	  timer_3s_cnt = 0;
BOOL  timer_3s_flag = FALSE;
BOOL  module_quit_flag = FALSE;

SEQ_NUM_T       me_seq_num = {15, 10, 04, 00, 00, 01};
ADDR_CODE_T     me_addr_code = {10, 00};
MT_FULL_T       me_mt_full = {06, 00};
MT_EMPTY_T      me_mt_empty = {04, 00};

PER_HIGH_T      me_per_high = {00, 80};
PER_LOW_T       me_per_low = {00, 20};

RESP_TIME_T     me_resp_time = {00, 06};

HV_800V_T       me_hv_value = {03, 00};
OP_TIME_T       me_op_time = {01, 00, 00, 00, 00, 00, 00, 00};

MODULE_STATE_ENUM  module_state = MODULE_STATE_INIT;
MODULE_STATE_ENUM  module_prevState = MODULE_STATE_INIT;

s16 ad_arr[150] = {0};

void variables_init(void)
{
  //led_500ms_start_flag = FALSE;
  //led_250ms_start_flag = FALSE;
  led_500ms_cnt = 0;
  led_250ms_cnt = 0;
  per_dly_1ms_cnt = 0;
  per_bypass_1ms_cnt = 0;
  timer_1ms_flag = FALSE;
  timer_100ms_flag = FALSE;
  timer_1000ms_flag = FALSE;
  g_addr_code = 0; 
  g_mt_full = 0;
  g_mt_empty = 0;
  g_per_high = 0;
  g_per_low = 0;
  g_resp_time = 0;

  g_hv_value = 0;
  g_disp_code = DISP_CODE_MIN;
  g_disp_para = 0;
}