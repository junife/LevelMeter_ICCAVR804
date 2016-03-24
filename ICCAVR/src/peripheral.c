//ICC-AVR application builder : 2015/10/1 19:02:47
// Target : M16
// Crystal: 1.0000Mhz

#include <iom16v.h>
#include <macros.h>
#include "peripheral.h"
#include "variables.h"

void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0x00;   //PA0, PA1, PA2 as ADC;  PA3,PA4,PA5 used as IO input 
 PORTB = 0x06;
 DDRB  = 0xFF;   //output
 PORTC = 0x00;   //m103 output only, 
 DDRC  = 0xFC;   //1: output, PC0, PC1 input
 PORTD = 0x00;
 DDRD  = 0x30;   //PD4,PD5 out
}

//Watchdog initialize
// prescale: 16K 
void watchdog_init(void)
{
 WDR(); //this prevents a timout on enabling
 WDTCR = 0x1F; 
 WDTCR = 0x0F; //WATCHDOG ENABLED - dont forget to issue WDRs
}

//TIMER0 initialize - prescale:Stop
// WGM: Normal
// desired value: 1000Hz
// actual value: Out of range
void timer0_init(void)
{
  TCCR0 |= 0x03;       //普通计时模式，普通端口操作，预分频为64   f=8M/64, T=64/8M = 8us
  TCNT0 = 131;		   //频率为2.5KHz	  1ms/8us = 125,   256-125=131  						 
  //SREG |= BIT(7);	   //开放全局中断   later we used SEI
  TIMSK |= BIT(TOIE0); //开放TIMER0溢出中断
}

//TIMER1 initialize - prescale:Stop
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 10Hz, 100ms
// actual value: Out of range
void timer1_init(void)
{
  TCCR1B = 0x03;   //预分频为64   f=8M/64, T=64/8M = 8us
  TCNT1H = 0xCF;   //100ms/8us = 12500, 65536-12500 = 53036, 0xCF2C
  TCNT1L = 0x2C;
  TIMSK |= BIT(TOIE1);  //开放TIMER1溢出中断
}


//UART0 initialize
// desired baud rate: 110
// actual: baud rate:110 (0.0%)
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = BIT(URSEL) | 0x06;
 UBRRL = 0x37; //set baud rate lo
 UBRRH = 0x02; //set baud rate hi
 UCSRB = 0x18;
}

//ADC initialize
// Conversion time: 26uS
void adc_init(void)
{
 ADCSR = 0x00; //disable adc
 ADMUX = 0x00; //select adc input 0
 ACSR  = 0x80;
 ADCSR = 0xE1;
}



u16 adc_start(u8 Num)
{
  u16 addata = 0;
  u16 poll = 0;
  //DDRA &= ~BIT(PA1); //PA1为输入状态,   0:In
  PORTA &= ~BIT(PA0); //PA0为高阻态输入
  PORTA &= ~BIT(PA1); //PA1为高阻态输入
  PORTA &= ~BIT(PA2); //PA2为高阻态输入
  ADMUX = 0x40;  //AVCC为基准电,AD1为输入通道 01000001
  switch(Num)
  {
    case AD0:
	  ADMUX = 0x40;  //AD0为输入通道 00000
	  break;
	  
	case AD1:
	  ADMUX = 0x41; //(1<< (AD1-1));  //AD1为输入通道 00001
	  break;
	  
	case AD2:      
	  ADMUX = 0x42; //(1<< (AD2-1));  //AD2为输入通道 00010
	  break;
	  
	default:
	  break;
  }

  ADCSR = 0x80;         //adc enable
  ADCSR |= BIT(ADSC);   //start convertion
  while( !(ADCSR&(BIT(ADIF))) && (poll++<1000) );
  if(poll>=1000)
  {
      poll = 0;
  }
  addata = ADCL;
  addata = addata+ADCH*256;
  return addata;
}   


//call this routine to initialize all peripherals
void peripheral_init(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 port_init();
 watchdog_init();
 timer0_init();
 timer1_init();
 uart0_init();
 adc_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x05; //timer interrupt sources
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}


//延迟函数
void Delay(signed int cnt)
{
   while(cnt>0)
   {
       cnt--;
   }
}

//延迟函数
void Per_Dly_Ms(signed int msCnt)
{
   per_dly_1ms_cnt = 0;
   while(per_dly_1ms_cnt < msCnt);
}

//延迟函数
BOOL Per_Bypass_Ms(signed int msCnt)
{
   if(per_bypass_1ms_cnt == 0)
   {
     per_bypass_1ms_cnt++;
   }
   if(per_bypass_1ms_cnt >= msCnt)
   {
     per_bypass_1ms_cnt = 0;
	 return TRUE;
   }
   return FALSE;
}