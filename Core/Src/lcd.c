#include "lcd.h"


#define   seg_a  0x01      //SEG0   //seg_e = 0x10  
#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
#define   seg_c  0x04      //SEG2 , //seg_g = 0x40
#define   seg_d  0x08      //SEG3 , //seg_d = 0x08
//High BIT
#define   seg_e  0x10      //SEG4 , //seg_c = 0x04
#define   seg_f  0x20      //SEG5   //seg_a = 0x01
#define   seg_g  0x40      //SEG6   //seg_b = 0x02 
#define   seg_h  0x80      //SEG7 -> ":"


#define  COM0_L        0x01
#define  COM1_L        0X02
#define  COM2_L        0X04
#define  COM3_L        0X08


#define  COM0_H        0X10
#define  COM1_H        0X20
#define  COM2_H        0X40
#define  COM3_H        0X80





const unsigned char segNumber_Low[]={
 
         seg_a+seg_b+seg_c+seg_d,        		// char "0"  0x00
		 seg_b+seg_c,                           // char "1"  0x01
		 seg_a+seg_b+seg_d,              		// char "2"  0x02
		 seg_a+seg_b+seg_c+seg_d,               // char "3"  0x03
		 seg_b+seg_c,                   	    // char "4"  0x04
		 seg_a+seg_c+seg_d,              		// char "5"  0x05
		 seg_a+seg_c+seg_d,              	    // char "6"  0x06
		 seg_a+seg_b+seg_c,                    	// char "7"  0x07
		 seg_a+seg_b+seg_c+seg_d,  		        // char "8"  0x08
		 seg_a+seg_b+seg_c+seg_d,        		// char "9"  0x09
	     0                                      // char "NLL"  0x16



};

const unsigned char segNumber_High[]={
         seg_e+seg_f,        		     // char "0"  0x00
		 0,//seg_b+seg_c,                // char "1"  0x01
		 seg_e+seg_g,              		 // char "2"  0x02
		 seg_g,                    		// char "3"  0x03
		 seg_f+seg_g,                    // char "4"  0x04
		 seg_f+seg_g,              		 // char "5"  0x05
		 seg_e+seg_f+seg_g,              // char "6"  0x06
		 0,                    		 	// char "7"  0x07
		 seg_e+seg_f+seg_g,  		     // char "8"  0x08
		 seg_f+seg_g,        		     // char "9"  0x09
         0                               // char "NLL"  0x16



};

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
static void TIM1723_Write_Cmd(uint8_t cmd);
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);

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
   //  Delay_us(150);
    data =data>>1;//
	 
	 TM1723_CLK_SetHigh();
	 //data =data>>1;//
	  Delay_us(2);
	// data >>=1;//
	
  
     
 }

}
static void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
     Delay_us(100);



}
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  // TM1723_STB_SetHigh();
   Delay_us(50);
  //  TM1723_STB_SetLow();
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();
   Delay_us(100);



}


/*************************************************************************
 	*
 	* Function Name:void Display_Name_AI(viod)
 	* Function :lcd display AI 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_AI(void)
{
	 TIM1723_Write_Cmd(0x00);
	// TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);


	
	//TM1723_Write_Display_Data(0xC2,0x00);
	TM1723_Write_Display_Data(0xC3,0x01);
	
	
    

	 //open display
	 TIM1723_Write_Cmd(OpenDispTM1723);
	 
	 
}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_Wifi(void)
 	* Function :lcd display WIFI
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_Wifi(void)
{
    TIM1723_Write_Cmd(0x00);
	// TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC5,0x01);

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723);
}
/*************************************************************************
 	*
 	* Function Name:void Display_Icon_Line(void)
 	* Function :lcd display '--------------'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Icon_Line(void)
{
	TIM1723_Write_Cmd(0x00);
	// TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC2,0x01);

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723);
	

}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_Dry(void)
 	* Function :lcd display 'DRY'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_Dry(void)
{
	 TM1723_STB_SetLow();
	 TM1723_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1723_STB_SetHigh();
    
     TM1723_STB_SetLow();
     TM1723_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1723_STB_SetHigh();

	//display "line"
	 TM1723_STB_SetLow();
     TM1723_Write_OneByte(0x0A);//SEG20
    
     TM1723_Write_OneByte(0x01);

     TM1723_STB_SetHigh();

	 //open display
	 TM1723_Start();
	 TM1723_Write_OneByte(OpenDispTM1723);
     TM1723_Stop();


}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_Kill(void)
 	* Function :lcd display 'kill'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_Kill(void)
{
	 TM1723_STB_SetLow();
	 TM1723_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1723_STB_SetHigh();
    
     TM1723_STB_SetLow();
     TM1723_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1723_STB_SetHigh();

	//display "line"
	 TM1723_STB_SetLow();
     TM1723_Write_OneByte(0x0C);//SEG24
    
     TM1723_Write_OneByte(0x01);

     TM1723_STB_SetHigh();

	 //open display
	 TM1723_Start();
	 TM1723_Write_OneByte(OpenDispTM1723);
     TM1723_Stop();

}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_ExpellingParasite(void);
 	* Function :lcd display 'expelling parasite'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_ExpellingParasite(void)
{
     TM1723_STB_SetLow();
	 TM1723_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1723_STB_SetHigh();
    
     TM1723_STB_SetLow();
     TM1723_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1723_STB_SetHigh();

	//display "line"
	 TM1723_STB_SetLow();
     TM1723_Write_OneByte(0x03);//SEG6
    
     TM1723_Write_OneByte(0x01);

     TM1723_STB_SetHigh();

	 //open display
	 TM1723_Start();
	 TM1723_Write_OneByte(OpenDispTM1723);
     TM1723_Stop();

}


