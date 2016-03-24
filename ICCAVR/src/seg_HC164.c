#include <iom16v.h>
#include <macros.h>
#include "segDisp.h"
#include "variables.h"
#include "peripheral.h"
#include "seg_HC164.h"

#define  CLK_HIGH        PORTC |= (1<<7)
#define  CLK_LOW         PORTC &= ~(1<<7)
#define  DATA_HIGH       PORTC |= (1<<6)
#define  DATA_LOW        PORTC &= ~(1<<6)

#define  SEG_DISP_RED    PORTC &= ~(1<<5); PORTC |= (1<<4) 
#define  SEG_DISP_GREEN  PORTC &= ~(1<<4); PORTC |= (1<<5)

//数组声明并定义在存储数据区code
//0~9
//#pragrma data:code  
//unsigned char const Number[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,};  //demo 共阴
unsigned char const Number_A[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xfe,0xf7};  //meter 共阳
//A~F
//#pragrma data:code
//unsigned char const Alpha[]={0x77,0x7c,0x39,0x5e,0x79,0x71,0x6f,0x5c,0x5e,0x00,};  //demo
unsigned char const Alpha_A[13]={0x88,0x83,0xc6,0xa1,0x86,0x8e,0x90,0xa3,0xa1,0x89,0xc1,0x82,0xff,};  //meter

//number show
void Seg_164_Number(u16 Num, SEG_COLOR_ENUM color, MARK_ENUM mark)
{
   u8 num[4] = {0}; //Thousand,Hundred,Ten,One;
   u8 i=0, j=0, temp=0;   
   num[0] = Num%10000/1000;     //thousand
   num[1] = Num%1000/100;       //hundred
   num[2] = Num%100/10;         //ten
   num[3] = Num%10;             //bit
   
   if(num[0] == 0)
   {
     num[0] = 10;
	 if(num[1] == 0)
	 {
	   if(mark == MARK_HIGH)
       {
   	     num[1] = 11;
       }
       else if(mark == MARK_LOW)
       {
         num[1] = 12;
       }
       else
       {
         num[1] = 10;
       }
	   
	   if(num[2] == 0)
	   {
	     num[2] = 10;
	   }
	 }
   }
   
   if(color == SEG_COLOR_RED)
   {
	 SEG_DISP_RED;
   }
   else if(color == SEG_COLOR_GREEN)
   {
	 SEG_DISP_GREEN;
   }
   else
   {
	 SEG_DISP_RED;
   }

   for(j=0; j<4; j++)
   {
     temp = Number_A[num[j]];
     for(i=0; i<8; i++)
	 {
	   CLK_LOW;
	   if(temp&0x80)  
	   {
	     DATA_HIGH;
	   }
	   else  
	   {           
	     DATA_LOW;
	   }
	   CLK_HIGH;
	   temp <<= 1;  //temp  = (Number_A[j] << 1);  //not same, why?
	 }
   }
}


//alpha show
//void Seg_Alpha_Show(Char alphabet1, Char alphabet2, Char alphabet3, Char alphabet4, s16 dlyCnt)
void Seg_164_Alpha(ALPHA_ENUM alphabet1, ALPHA_ENUM alphabet2, ALPHA_ENUM alphabet3,
                   ALPHA_ENUM alphabet4, SEG_COLOR_ENUM color)
{
   u8 alpha[4] = {0};
   u8 i, j, temp;
   alpha[0] = alphabet1;
   alpha[1] = alphabet2;
   alpha[2] = alphabet3;
   alpha[3] = alphabet4;
   
   for(j=0; j<4; j++)
   {
     temp = Alpha_A[alpha[j]];
     for(i=0; i<8; i++)
	 {
	   CLK_LOW;
	   if(temp&0x80)  
	   {
	     DATA_HIGH;
	   }
	   else  
	   {           
	     DATA_LOW;
	   }
	   CLK_HIGH;
	   temp <<= 1;
	 }
   }
   
   if(color == SEG_COLOR_RED)
   {
     SEG_DISP_RED;
   }
   else if(color == SEG_COLOR_GREEN)
   {
     SEG_DISP_GREEN;
   }
   else
   {
   }
}







