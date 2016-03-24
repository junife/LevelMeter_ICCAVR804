#ifndef  SEG_HC164_H    //使用_和 __ 开始的函数一般都是专用的函数，一般都是于特定系统相关的，
#define  SEG_HC164_H     //如果要想有更好的移植性，应该避免使用

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