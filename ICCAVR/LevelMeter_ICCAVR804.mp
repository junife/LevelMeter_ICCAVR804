Project:      ..\LevelMeter_ICCAVR804\LevelMeter_ICCAVR804
Build Number: 5
Date:         Thu Mar 24 23:51:11 2016
Compiler:     ICCAVR
Version:      8.04.03

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0054   0008 =      8. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __lit_start
       005C  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   005C   02B9 =    697. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       005C  __idata_start
       0315  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0316   21EE =   8686. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       018B  __start
       018B  __text_start
       01AD  _exit
       01AE  _Button_Scan
       0374  _Con_Module_Init_Proc
       0468  _Con_Module_Work_Norm_Proc
       047C  _Con_Module_Work_Warn_Proc
       0487  _Con_Module_Communicate_Proc
       0488  _Con_Module_Service_Proc
       0490  _Con_Module_Error_Proc
       0491  _Con_Module_Quit_Proc
       04AC  _PORT_KZ1_HIGH_IN
       04BC  _PORT_KZ2_LOW_IN
       04CA  _getMaxVal
       04F3  _getAvgVal
       052E  _materialDetect
       06E4  _buttonDetect
       0C87  _Con_Monitor
       0CA1  _timer0_ovf_isr
       0D1F  _timer1_ovf_isr
       0D38  _LedLight
       0D4A  _LedBlink
       0D93  _main
       0DDA  _EEPROM_Write_One_Byte
       0DF7  _EEPROM_Read_One_Byte
       0E0E  _EEPROM_Write_Bytes
       0E25  _EEPROM_Read_Bytes
       0E52  _port_init
       0E60  _watchdog_init
       0E66  _timer0_init
       0E6F  _timer1_init
       0E79  _uart0_init
       0E85  _adc_init
       0E8D  _adc_start
       0ECF  _peripheral_init
       0EDD  _Delay
       0EE6  _Per_Dly_Ms
       0EF4  _Per_Bypass_Ms
       0F13  _Seg_Number_Show
       0F85  _Seg_Deci_Show
       0FF9  _Seg_Alpha_Show
       104B  segDisp.c:Clear_Show
       1050  _Seg_164_Number
       10D4  _Seg_164_Alpha
       1116  _variables_init
       1151  mod16u
       1153  div16u
       1154  xdiv16u
       116D  div32u
       116F  mod32u
       1173  div32s
       1175  mod32s
       11A1  long_div_prolog
       11B4  long_div_epilog
       11C4  tst_R16_R19
       11C9  tst_R24_R27
       11CE  neg_R24_R27
       11D7  mod8u
       11D9  div8u
       11DA  xdiv8u
       11EF  empy16s
       11FF  pop_xgset30FC
       1208  pop_xgsetF0FC
       1213  push_xgsetF0FC
       1215  push_xgset30FC
       1217  push_xgset00FC
       1219  push_xgset003C
       121E  push_xgset300C
       1223  pop_xgset300C
       1228  push_xgsetF000
       122D  pop_xgsetF000
       1232  push_xgsetF00C
       1239  pop_xgsetF00C
       1240  push_xgset303C
       1247  pop_xgset303C
       124E  push_xgsetF03C
       1257  pop_xgsetF03C
       1260  neg32
       1269  asgncblk
       1282  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   02B9 =    697. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _button
       0060  __data_start
       0072  control.c:tickCnt
       0189  _Number
       0194  _Alpha
       01A1  _Number_A
       01AE  _Alpha_A
       01BB  _eeprom_buf
       01CB  _timer_3s_cnt
       01CD  _timer_3s_flag
       01CE  _module_quit_flag
       01CF  _me_seq_num
       01D5  _me_addr_code
       01D7  _me_mt_full
       01D9  _me_mt_empty
       01DB  _me_per_high
       01DD  _me_per_low
       01DF  _me_resp_time
       01E1  _me_hv_value
       01E3  _me_op_time
       01EB  _module_state
       01EC  _module_prevState
       01ED  _ad_arr
       0319  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0319   001C =     28. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0319  _g_disp_code
       0319  __bss_start
       031A  _g_disp_para
       031C  _g_hv_value
       031E  _g_resp_time
       0320  _g_per_low
       0322  _g_per_high
       0324  _g_mt_empty
       0326  _g_mt_full
       0328  _g_addr_code
       032A  _timer_1000ms_flag
       032B  _timer_100ms_flag
       032C  _timer_1ms_flag
       032D  _per_bypass_1ms_cnt
       032F  _per_dly_1ms_cnt
       0331  _led_250ms_cnt
       0333  _led_500ms_cnt
       0335  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0028 =     40. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.objs\src\button.o	[ button.c ]
.objs\src\control.o	[ control.c ]
.objs\src\interrupt.o	[ interrupt.c ]
.objs\src\led.o	[ led.c ]
.objs\src\main.o	[ main.c ]
.objs\src\memory.o	[ memory.c ]
.objs\src\peripheral.o	[ peripheral.c ]
.objs\src\segDisp.o	[ segDisp.c ]
.objs\src\seg_HC164.o	[ seg_HC164.c ]
.objs\src\variables.o	[ variables.c ]
.objs\src\wireless.o	[ wireless.c ]
<library>	[ div16u.s, div32.s, div8u.s, emul16s.s, gpop4.s, gpop5.s, gpush.s, gpushx.s, gpushy.s, gpushz.s, gpusha.s ]
[ gpushb.s, lneg.s, pmstruct.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0x54.0x4000
-bdata:0x60.0x45f

