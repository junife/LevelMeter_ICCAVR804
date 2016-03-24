#include <iom16v.h>
#include <macros.h>
#include "segDisp.h"
#include "variables.h"
#include "peripheral.h"

static void Clear_Show(void);

//���������������ڴ洢������code
//0~9
//#pragrma data:code  
//unsigned char const Number[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,};  //demo ����
unsigned char const Number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,};  //meter ����
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
   Hundred=Num%1000/100;       //ȡ��λ
   Ten=Num%100/10;        //ȡʮλ
   One=Num%10;            //ȡ��λ  
   
   //��ʾthousandλ   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Thousand];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(0);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);         //��΢�ӳ� 
   
   //��ʾ��λ   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Hundred];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(1);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);         //��΢�ӳ� 
   
   //��ʾʮλ
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Ten];  //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(2);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ

   Delay(dlyCnt);         //��΢�ӳ�
   
   //��ʾ��λ
   Clear_Show();       //bit selection clear
   
   PORTB=Number[One];  //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(3);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);        //��΢�ӳ�  
}

//Bytes show
void Seg_Deci_Show(u16 intNum, s16 dlyCnt)
{
   unsigned char Thousand,Hundred,Ten,One;
   Thousand = (intNum>>8)%100/10;   
   Hundred = (intNum>>8)%10;          //ȡ��λ
   Ten = (intNum&0xFF)%100/10;        //ȡʮλ
   One = (intNum&0xFF)%10;            //ȡ��λ  
   
   //��ʾthousandλ   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Thousand];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(0);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);         //��΢�ӳ� 
   
   //��ʾ��λ   
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Hundred];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(1);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);         //��΢�ӳ� 
   
   //��ʾʮλ
   Clear_Show();       //bit selection clear 
   
   PORTB=Number[Ten];  //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(2);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ

   Delay(dlyCnt);         //��΢�ӳ�
   
   //��ʾ��λ
   Clear_Show();       //bit selection clear
   
   PORTB=Number[One];  //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(3);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);        //��΢�ӳ�  
}


//alpha show
//void Seg_Alpha_Show(Char alphabet1, Char alphabet2, Char alphabet3, Char alphabet4, s16 dlyCnt)
void Seg_Alpha_Show(ALPHA_ENUM alphabet1, ALPHA_ENUM alphabet2,
                    ALPHA_ENUM alphabet3, ALPHA_ENUM alphabet4, s16 dlyCnt)
{
   //unsigned char Hundred,Ten,One;
   //Hundred=Num/100;       //ȡ��λ
   //Ten=Num%100/10;        //ȡʮλ
   //One=Num%10;            //ȡ��λ
   
   //��ʾthousandλ   
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet1];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(0);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   Delay(dlyCnt);         //��΢�ӳ� 
   
   //��ʾhundredλ
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet2];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(1);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   
   Delay(dlyCnt);         //��΢�ӳ�
   
   //��ʾtenλ
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet3];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(2);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   
   Delay(dlyCnt);        //��΢�ӳ�  
   
   //��ʾbitλ
   Clear_Show();       //bit selection clear 
   
   PORTB=Alpha[alphabet4];     //��ģ��
   PORTA|=BIT(PA3);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA3);   //PA3�͵�ƽ
   
   PORTB=~BIT(3);      //��λѡ
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
   
   Delay(dlyCnt);        //��΢�ӳ�  
}


static void Clear_Show(void)
{
   PORTB=~BIT(7);      //��λѡ8, not used
   PORTA|=BIT(PA4);    //PA3�ߵ�ƽ
   PORTA&=~BIT(PA4);   //PA3�͵�ƽ
}

