#ifndef  SEGDISP_H    //ʹ��_�� __ ��ʼ�ĺ���һ�㶼��ר�õĺ�����һ�㶼�����ض�ϵͳ��صģ�
#define  SEGDISP_H     //���Ҫ���и��õ���ֲ�ԣ�Ӧ�ñ���ʹ��
//#define  __SEGDISP_H    //don't use, �»��߱�ANSIԼ�������ڲ�������

#include "variables.h"

//ö�ٱ���aplha����
typedef enum {A,B,C,D,E,F,g,o,d,H,U,G}ALPHA_ENUM;

extern unsigned char const Number[];
//A~F
//#pragrma data:code
extern unsigned char const Alpha[];

void Seg_Number_Show(u16 Num, s16 dlyCnt); 
void Seg_Alpha_Show(ALPHA_ENUM alphabet1, ALPHA_ENUM alphabet2, 
                    ALPHA_ENUM alphabet3, ALPHA_ENUM alphabet4, s16 dlyCnt);
//void Alpha_Show(alpha alphabet1, alpha alphabet2, alpha alphabet3, s16 dlyCnt);  //error

#endif
