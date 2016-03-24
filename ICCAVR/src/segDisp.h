#ifndef  SEGDISP_H    //使用_和 __ 开始的函数一般都是专用的函数，一般都是于特定系统相关的，
#define  SEGDISP_H     //如果要想有更好的移植性，应该避免使用
//#define  __SEGDISP_H    //don't use, 下划线被ANSI约定用作内部库命名

#include "variables.h"

//枚举变量aplha声明
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
