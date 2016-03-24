#ifndef  SEG_HC164_H    //ʹ��_�� __ ��ʼ�ĺ���һ�㶼��ר�õĺ�����һ�㶼�����ض�ϵͳ��صģ�
#define  SEG_HC164_H     //���Ҫ���и��õ���ֲ�ԣ�Ӧ�ñ���ʹ��

#include "variables.h"


typedef enum mark
{
   MARK_HIGH,
   MARK_LOW,
   MARK_NULL,
} MARK_ENUM;

typedef enum seg_color
{
   SEG_COLOR_RED,
   SEG_COLOR_GREEN,
} SEG_COLOR_ENUM;

void Seg_164_Number(u16 Num, SEG_COLOR_ENUM color, MARK_ENUM mark);

void Seg_164_Alpha(ALPHA_ENUM alphabet1, ALPHA_ENUM alphabet2, ALPHA_ENUM alphabet3,
                   ALPHA_ENUM alphabet4, SEG_COLOR_ENUM color);


#endif