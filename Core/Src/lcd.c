#include "lcd.h"


static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
void Bdelay_us(uint16_t t);

//static void Send_Command(uint8_t com);
static void Delay_us(uint8_t t);


static void Delay_us(uint8_t t)
{
  uint16_t j;
	for(j=0;j<t;j++)
	{
       for(int i = 0; i <50; i++)//better for(int i = 0; i < 40; i++)    //for(int i = 0; i < 20; i++)    
        {
            __asm("NOP");//等待1个指令周期，系统主频24M
           
        }
	}
}


/*****************************************************
 * 
 * 
 * 
 * 
******************************************************/
static void TM1723_Start(void)
{
  TM1723_STB_SetLow();
	
}
static void TM1723_Stop(void)
{
   TM1723_STB_SetHigh();

}

static void TM1723_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1723_CLK_SetLow();
	 if(data & 0x01){
	     TM1723_DIO_SetHigh();
		   //HAL_Delay(5); //5ms
	 }
	 else{
	     TM1723_DIO_SetLow();
		  // HAL_Delay(5); //5ms
	 
	 }
	// HAL_Delay(1); //5ms
    Delay_us(150);
	 
	 TM1723_CLK_SetHigh();
	 data >>=1;//
	
  
     
 }

}

