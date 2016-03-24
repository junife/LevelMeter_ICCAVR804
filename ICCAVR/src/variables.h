#ifndef VARIABLES_H
#define VARIABLES_H


//#define  u8    unsigned char
//#define  s8    signed char
//#define  u16   unsigned int
//#define  s16   signed int     //error
//typedef  unsigned char   u8   //error, no ";"

#define  HOLD_TIME_3S      30  //button scan, 100ms time_tick
#define  HOLD_TIME_0_5S    5   //button scan, 100ms time_tick
#define  HOLD_TIME_0_1S    1   //button scan, 100ms time_tick
#define  TRUE              1
#define  FALSE             0
#define  ON                1
#define  OFF               0
#define  HIGH              1
#define  LOW               0


typedef  unsigned char   BOOL;

typedef  unsigned char   u8;    
typedef  signed char     s8;    
typedef  unsigned int    u16;   
typedef  signed int      s16;  
typedef  unsigned long   u32;   
typedef  signed long     s32;   

typedef enum disp_code_enum
{
   DISP_CODE_MIN = 0,
   DISP_CODE_0 = 1,     //DISP_CODE_0 = 1,

   DISP_CODE_1 = 2,     //g_mt_empty 
   DISP_CODE_2 = 3,     //g_mt_full
   
   DISP_CODE_3 = 4,    //g_per_low
   DISP_CODE_4 = 5,    //g_per_high
   
   DISP_CODE_5 = 6,    //g_resp_time +
   DISP_CODE_6 = 7,    //g_resp_time -
   
   DISP_CODE_7 = 8,    //address +
   DISP_CODE_8 = 9,    //address -
       
   DISP_CODE_MAX = 10,
} DISP_CODE_ENUM;


typedef enum module_state_enum
{
   MODULE_STATE_MIN,
   MODULE_STATE_INIT,
   MODULE_STATE_WORK_NORM,
   MODULE_STATE_WORK_WARN,
   MODULE_STATE_COMMUNICATE,
   MODULE_STATE_SERVICE,
   MODULE_STATE_ERROR,
   MODULE_STATE_QUIT,
   MODULE_STATE_MAX
} MODULE_STATE_ENUM;


typedef enum serv_state_enum
{
   SERV_STATE_MIN,
   SERV_STATE_RESET,
   SERV_STATE_DISP_CODE,
   SERV_STATE_CODE_CHANGE,
   SERV_STATE_DISP_PARA,
   SERV_STATE_PARA_CHANGE,
   SERV_STATE_PARA_SAVE,
   SERV_STATE_MAX
} SERV_STATE_ENUM;


typedef struct seq_num_tag
{
  u8 year;
  u8 month;
  u8 day;
  u8 highBytes;
  u8 midBytes;
  u8 lowBytes;
}SEQ_NUM_T;

typedef struct addr_code_tag
{
  u8 highByte;
  u8 lowByte;
}ADDR_CODE_T;

typedef struct mt_full_tag
{
  u8 highByte;
  u8 lowByte;
}MT_FULL_T;

typedef struct mt_empty_tag
{
  u8 highByte;
  u8 lowByte;
}MT_EMPTY_T;

typedef struct per_high_tag
{
  u8 highByte;
  u8 lowByte;
}PER_HIGH_T;

typedef struct per_low_tag
{
  u8 highByte;
  u8 lowByte;
}PER_LOW_T;

typedef struct resp_time_tag
{
  u8 highByte;
  u8 lowByte;
}RESP_TIME_T;

typedef struct hv_800v_tag
{
  u8 highByte;
  u8 lowByte;
}HV_800V_T;


typedef struct op_time_tag
{
  u8 val[8];
}OP_TIME_T;


//extern BOOL  led_500ms_start_flag;
//extern BOOL  led_250ms_start_flag;
extern u16   led_500ms_cnt;
extern u16   led_250ms_cnt;
extern u16   per_dly_1ms_cnt;
extern u16   per_bypass_1ms_cnt;
extern BOOL  timer_1ms_flag;
extern BOOL  timer_100ms_flag;
extern BOOL  timer_1000ms_flag;

extern SEQ_NUM_T       me_seq_num;
extern ADDR_CODE_T     me_addr_code;
extern MT_FULL_T       me_mt_full;
extern MT_EMPTY_T      me_mt_empty;
extern PER_HIGH_T      me_per_high;
extern PER_LOW_T       me_per_low;
extern RESP_TIME_T     me_resp_time;
extern HV_800V_T       me_hv_value;
extern OP_TIME_T       me_op_time;
extern u16             g_addr_code; 
extern u16             g_mt_full;
extern u16             g_mt_empty;

extern u16             g_per_high;
extern u16             g_per_low;

extern u16             g_resp_time;
extern u16             g_hv_value;
extern u16             g_disp_para;
extern u8              eeprom_buf[16];
extern u16	           timer_3s_cnt;
extern BOOL            timer_3s_flag;
extern BOOL            module_quit_flag;

extern MODULE_STATE_ENUM   module_state;
extern MODULE_STATE_ENUM   module_prevState;
extern DISP_CODE_ENUM      g_disp_code;

extern s16             ad_arr[150];

extern void variables_init(void);

#endif