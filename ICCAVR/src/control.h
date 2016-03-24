#ifndef CONTROL_H
#define CONTROL_H

#define  KZ1_OUT_LOW()    PORTD &= ~BIT(4)
#define  KZ2_OUT_HIGH()   PORTD |= BIT(5)

#define  RL1_CLOSE()      PORTC &= ~BIT(2)   //norm
#define  RL1_OPEN()       PORTC |= BIT(2)    //warn

#define  RL2_CLOSE()      PORTC &= ~BIT(3)   //norm
#define  RL2_OPEN()       PORTC |= BIT(3)    //warn

#define  AD_KZ1           AD0
#define  AD_KZ2           AD1

#define  FG_IO_IN()       (PINA & BIT(4)) >> 4

void Con_Module_Init_Proc(void);
void Con_Module_Work_Norm_Proc(void);
void Con_Module_Work_Warn_Proc(void);
void Con_Module_Communicate_Proc(void);
void Con_Module_Service_Proc(void);
void Con_Module_Error_Proc(void);
void Con_Module_Quit_Proc(void);
u8 PORT_KZ1_HIGH_IN(void);    
u8 PORT_KZ2_LOW_IN(void);
void getMaxVal(u16 length, u16 inData, u16* maxArray);
u32 getAvgVal(u16 length, u16* inArray);
void materialDetect(void);
void buttonDetect(void);
void Con_Monitor(void);

#endif