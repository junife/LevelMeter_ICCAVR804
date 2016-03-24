#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"
#include "memory.h"

//��EEPROM����
void EEPROM_Write_One_Byte(u16 Addr, u8 Data)
{
  u8 poll = 0;
  if(Addr < 512)	//�����ַ����512����Ч
  {
    while( (EECR&BIT(EEWE)) && (poll<100) ) 	//��ѯ��һ��EEPROMд�����Ƿ����
	{
	  poll++;
	  asm("nop");
	}
    EEAR = Addr;			//д���ַ
    EEDR = Data;			//д������
	CLI(); //disable all interrupts
    EECR |= BIT(EEMWE);		//EEPROMд����ʹ�ܣ�׼��
    EECR |= BIT(EEWE);		//EEPROMдʹ�ܣ�д��
	SEI(); //re-enable interrupts
	Per_Dly_Ms(50);   //must have some delay time!!!!  5ms is not ok!!!
  }
}

//��EEPROM����
u8 EEPROM_Read_One_Byte(u16 Addr)
{
  u8 Temp=0, poll=0;
  if(Addr < 512)  //�����ַ����512����ȡ0ֵ
  {
    while( (EECR&BIT(EEWE)) && (poll++<100) );	//��ѯ��һ��EEPROMд�����Ƿ����
    EEAR = Addr;				//д���ַ
    EECR |= BIT(EERE);		//EEPROM��ʹ�ܣ�����
    Temp = EEDR;				//��ȡ����
  }	
  return Temp;				//��������
}

//write EEPROM����, several bytes
void EEPROM_Write_Bytes(u16 startAddr, u8 *bufferIn, u16 size)
{
  u16 i=0;
  for(i=0; i<size; i++)
  {
    EEPROM_Write_One_Byte(startAddr+i, *(bufferIn++));
  }
}

//��EEPROM����, several bytes
void EEPROM_Read_Bytes(u16 startAddr, u8 *bufferOut, u16 size)
{
  u16 i=0, poll=0;
  while(i<size)
  {
    if(startAddr+i < 512)
	{
	  while((EECR&BIT(EEWE)) && (poll<100))	//��ѯ��һ��EEPROMд�����Ƿ����
	  {
	    poll++;
	    asm("nop");
	  }
      EEAR = startAddr+i;				//д���ַ
      EECR |= BIT(EERE);		//EEPROM��ʹ�ܣ�����
	  *(bufferOut++) = EEDR;	//��ȡ����
	  poll = 0;
	  i++;
	}
	else
	{
	  break;  //error, out of range
	}
  }
}



//����ڲ���5 ��6 ֮�䷢�����жϣ�д������ʧ�ܡ���Ϊ��ʱEEPROM дʹ�ܲ�
//������ʱ�����һ������EEPROM���жϴ������һ��EEPROM������EEAR ��EEDR
//�Ĵ������ܱ��޸ģ�����EEPROM ����ʧ�ܡ������ʱ�ر�ȫ���жϱ�־I��


//(2)�ȴ�SPMCSR �е�SPMEN λ��Ϊ��
//��CPU дFlash �洢����ʱ���ܶ�EEPROM ���б�̡�������EEPROM д����֮
//ǰ��������� Flash д�����Ƿ��Ѿ���ɡ�����(2) �����������������������CPU
//��Flash ���б��ʱ�����á����CPU ��Զ������дFlash������(2) ��ʡ�ԡ�


//����EEPROM����ù��жϡ����⻹Ҫ�ǵô�BODŶ��
//��λEEWE������д������ASM ����û����, C ���򳬹�������ʱ��(�ĸ�����)��
//������ʱ��(�ĸ�����)����Ϊ�Ż������ʱ����SFR��RAM�������ų�ʱ�ġ��Ż���0��֮������������Ϳ����ˡ�

  /*u16 i=0, poll=0;   //why this not ok?
  while(i<size)
  {
    if(startAddr+i < 512)
	{
	  while((EECR&BIT(EEWE)) && (poll++<1000));	//��ѯ��һ��EEPROMд�����Ƿ����
	  EEAR = startAddr+i;			    //д���ַ
      EEDR = *(bufferIn++);	    //д������
	  CLI(); //disable all interrupts
      EECR |= BIT(EEMWE);		//EEPROMд����ʹ�ܣ�׼��
      EECR |= BIT(EEWE);		//EEPROMдʹ�ܣ�д��
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