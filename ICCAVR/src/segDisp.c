#include <iom16v.h>
#include <macros.h>
#include "segDisp.h"
#include "variables.h"
#include "peripheral.h"

static void Clear_Show(void);

//数组声明并定义在存储数据区code
//0~9
//#pragrma data:code  
//unsigned char const Number[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,};  //demo 共阴
unsigned char const Number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,};  //meter 共阳
//A~F
//#pragrma data:code
//unsigned char const Alpha[]={0x77,0x7c,0x39,0x5e,0x79,0x71,0x6f,0x5c,0x5e,0x00,};  //demo
unsigned char const Alpha[]={0x88,0x83,0xc6,0xa1,0x86,0x8e,0x90,0xa3,0xa1,0x89,0xc1,0x82,0xff,};  //meter
                            //A,  B,   C,    D,   E,   F,   g,   o,   d,   H,   U,   G, 
//number show
void Seg_Number_Show(u16 Num, s16 dlyCnt)
{
   unsigned char Thousand,Hundred,Ten,One;
   Thousand = Num%10000/1000;   
   Hundred=Num%1000/100;       //取百位
   Ten=Num%100/10;        //取十位
   One=Num%10;            //取个位  
   
   //显示thousand位   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Thousand];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(0);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);         //稍微延迟 
   
   //显示百位   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Hundred];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(1);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);         //稍微延迟 
   
   //显示十位
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Ten];  //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(2);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平

   Delay(dlyCnt);         //稍微延迟
   
   //显示个位
   Clear_Show();       //bit selection clear
   
   PORTB=Number[One];  //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(3);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);        //稍微延迟  
}

//Bytes show
void Seg_Deci_Show(u16 intNum, s16 dlyCnt)
{
   unsigned char Thousand,Hundred,Ten,One;
   Thousand = (intNum>>8)%100/10;   
   Hundred = (intNum>>8)%10;          //取百位
   Ten = (intNum&0xFF)%100/10;        //取十位
   One = (intNum&0xFF)%10;            //取个位  
   
   //显示thousand位   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Thousand];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(0);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);         //稍微延迟 
   
   //显示百位   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Hundred];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(1);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);         //稍微延迟 
   
   //显示十位
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Ten];  //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(2);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平

   Delay(dlyCnt);         //稍微延迟
   
   //显示个位
   Clear_Show();       //bit selection clear
   
   PORTB=Number[One];  //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(3);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);        //稍微延迟  
}


//alpha show
//void Seg_Alpha_Show(Char alphabet1, Char alphabet2, Char alphabet3, Char alphabet4, s16 dlyCnt)
void Seg_Alpha_Show(ALPHA_ENUM alphabet1, ALPHA_ENUM alphabet2,
                    ALPHA_ENUM alphabet3, ALPHA_ENUM alphabet4, s16 dlyCnt)
{
   //unsigned char Hundred,Ten,One;
   //Hundred=Num/100;       //取百位
   //Ten=Num%100/10;        //取十位
   //One=Num%10;            //取个位
   
   //显示thousand位   
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet1];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(0);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   Delay(dlyCnt);         //稍微延迟 
   
   //显示hundred位
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet2];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(1);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   
   Delay(dlyCnt);         //稍微延迟
   
   //显示ten位
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet3];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(2);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   
   Delay(dlyCnt);        //稍微延迟  
   
   //显示bit位
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet4];     //送模码
   PORTA|=BIT(PA3);    //PA3高电平
   PORTA&=~BIT(PA3);   //PA3低电平
   
   PORTB=~BIT(3);      //送位选
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
   
   Delay(dlyCnt);        //稍微延迟  
}


static void Clear_Show(void)
{
   PORTB=~BIT(7);      //送位选8, not used
   PORTA|=BIT(PA4);    //PA3高电平
   PORTA&=~BIT(PA4);   //PA3低电平
}

