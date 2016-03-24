#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"
#include "memory.h"

//读EEPROM函数
void EEPROM_Write_One_Byte(u16 Addr, u8 Data)
{
  u8 poll = 0;
  if(Addr < 512)	//如果地址大于512，无效
  {
    while( (EECR&BIT(EEWE)) && (poll<100) ) 	//查询上一次EEPROM写操作是否完成
	{
	  poll++;
	  asm("nop");
	}
    EEAR = Addr;			//写入地址
    EEDR = Data;			//写入数据
	CLI(); //disable all interrupts
    EECR |= BIT(EEMWE);		//EEPROM写主机使能：准备
    EECR |= BIT(EEWE);		//EEPROM写使能：写入
	SEI(); //re-enable interrupts
	Per_Dly_Ms(50);   //must have some delay time!!!!  5ms is not ok!!!
  }
}

//读EEPROM函数
u8 EEPROM_Read_One_Byte(u16 Addr)
{
  u8 Temp=0, poll=0;
  if(Addr < 512)  //如果地址大于512，读取0值
  {
    while( (EECR&BIT(EEWE)) && (poll++<100) );	//查询上一次EEPROM写操作是否完成
    EEAR = Addr;				//写入地址
    EECR |= BIT(EERE);		//EEPROM读使能：读出
    Temp = EEDR;				//读取数据
  }	
  return Temp;				//返回数据
}

//write EEPROM函数, several bytes
void EEPROM_Write_Bytes(u16 startAddr, u8 *bufferIn, u16 size)
{
  u16 i=0;
  for(i=0; i<size; i++)
  {
    EEPROM_Write_One_Byte(startAddr+i, *(bufferIn++));
  }
}

//读EEPROM函数, several bytes
void EEPROM_Read_Bytes(u16 startAddr, u8 *bufferOut, u16 size)
{
  u16 i=0, poll=0;
  while(i<size)
  {
    if(startAddr+i < 512)
	{
	  while((EECR&BIT(EEWE)) && (poll<100))	//查询上一次EEPROM写操作是否完成
	  {
	    poll++;
	    asm("nop");
	  }
      EEAR = startAddr+i;				//写入地址
      EECR |= BIT(EERE);		//EEPROM读使能：读出
	  *(bufferOut++) = EEDR;	//读取数据
	  poll = 0;
	  i++;
	}
	else
	{
	  break;  //error, out of range
	}
  }
}



//如果在步骤5 和6 之间发生了中断，写操作将失败。因为此时EEPROM 写使能操
//作将超时。如果一个操作EEPROM的中断打断了另一个EEPROM操作，EEAR 或EEDR
//寄存器可能被修改，引起EEPROM 操作失败。建议此时关闭全局中断标志I。


//(2)等待SPMCSR 中的SPMEN 位变为零
//在CPU 写Flash 存储器的时候不能对EEPROM 进行编程。在启动EEPROM 写操作之
//前软件必须检查 Flash 写操作是否已经完成。步骤(2) 仅在软件包含引导程序并允许CPU
//对Flash 进行编程时才有用。如果CPU 永远都不会写Flash，步骤(2) 可省略。


//操作EEPROM，最好关中断。另外还要记得打开BOD哦。
//置位EEWE以启动写操作。ASM 程序没问题, C 程序超过了容许时限(四个周期)。
//超容许时限(四个周期)是因为优化级最低时，把SFR当RAM操作，才超时的。优化到0级之外的其它级，就可以了。

  /*u16 i=0, poll=0;   //why this not ok?
  while(i<size)
  {
    if(startAddr+i < 512)
	{
	  while((EECR&BIT(EEWE)) && (poll++<1000));	//查询上一次EEPROM写操作是否完成
	  EEAR = startAddr+i;			    //写入地址
      EEDR = *(bufferIn++);	    //写入数据
	  CLI(); //disable all interrupts
      EECR |= BIT(EEMWE);		//EEPROM写主机使能：准备
      EECR |= BIT(EEWE);		//EEPROM写使能：写入
	  SEI(); //re-enable interrupts
	  Delay(100);
	  poll = 0;
	  i++;
	}
	else
	{
	  break;  //error, out of range
	}
  }*/