#ifndef MEMORY_H
#define MEMORY_H


#define  SEQ_NUM_ADDR         0x0   //format: yymmddxxxxxx
#define  ADDR_CODE_ADDR       0x10
#define  MT_FULL_ADDR         0x20
#define  MT_EMPTY_ADDR        0x28
#define  PER_HIGH_ADDR        0x30 
#define  PER_LOW_ADDR         0x38 
#define  RESP_TIME_ADDR       0x40 
#define  OP_TIME_LOW_ADDR     0x50  //0x0000->0xFF00->0xFF01->0xFFFF...
#define  OP_TIME_HIGH_ADDR    0x58  //if LOW_ADDR is all 0xFF, then HIGH_ADDR "+1", clear LOW_ADDR to 0x00
#define  HV_800V_ADDR         0x60 
#define  ERROR_LOG_ADDR       0x70 
#define  EEPROM_START_ADDR    0x0     
#define  EEPROM_END_ADDR      0x1FF   

#define  MT_FULL              600  
#define  MT_EMPTY             400    
#define  PER_HIGH             80  
#define  PER_LOW              20  

#define  RESP_TIME_VALUE      3     //unit: second

#define  HV_800V_VALUE        300
#define  ADDR_CODE_VALUE      1000

#define  DISP_PARA_MAX        1000
#define  DISP_PARA_MIN        100

u8 EEPROM_Erase(u16 startAddr, u16 endAddr);

void EEPROM_Write_One_Byte(u16 Addr, u8 Data);
u8 EEPROM_Read_One_Byte(u16 Addr);

void EEPROM_Write_Bytes(u16 startAddr, u8 *bufferIn, u16 size);
void EEPROM_Read_Bytes(u16 startAddr, u8 *bufferOut, u16 size);

//0x0: sequence no.
//0x20: High Threshhold
//0x30: Low  Threshhold
//0x40: operation time
//0x50: error log 

#endif