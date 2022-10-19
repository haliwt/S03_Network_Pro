#include "lcd.h"
#include "delay.h"


#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
#define   seg_g  0x04      //SEG2 , //seg_g = 0x40
#define   seg_c  0x08      //SEG3 , //seg_d = 0x08
//High BIT
#define   seg_a  0x10      //SEG4 , //seg_c = 0x04
#define   seg_f  0x20      //SEG5   //seg_a = 0x01
#define   seg_e  0x40      //SEG6   //seg_b = 0x02 
#define   seg_d  0x80      //SEG7 -> ":"


#define  COM0_L        0x01
#define  COM1_L        0X02
#define  COM2_L        0X04
#define  COM3_L        0X08


#define  COM0_H        0X10
#define  COM1_H        0X20
#define  COM2_H        0X40
#define  COM3_H        0X80


const uint8_t lcdNumber_Low[]={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0E,0x0A,0x0E,0x0E,0x00};


const unsigned char segNumber_Low[]={
 
         seg_b+seg_c,        		      // char "0"  0x00
		 seg_b+seg_c,                      // char "1"  0x01
		 seg_b+seg_g,              		  // char "2"  0x02
		 seg_b+seg_g+seg_c,               // char "3"  0x03
		 seg_b+seg_g+seg_c,               // char "4"  0x04
		 seg_g+seg_c,              		// char "5"  0x05
		 seg_a+seg_g+seg_c,              // char "6"  0x06
		 seg_b+seg_c,                    	// char "7"  0x07
		 seg_b+seg_g+seg_c,  		        // char "8"  0x08
		 seg_b+seg_g+seg_c,        		// char "9"  0x09
	     0                                      // char "NLL"  0x16



};

const uint8_t  lcdNumber_High[]={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};
const unsigned char segNumber_High[]={
         seg_a+seg_f+seg_e+seg_d,        // char "0"  0x00
		 0,                				 // char "1"  0x01
		 seg_a+seg_e+seg_d,              // char "2"  0x02
		 seg_a+seg_d,                    // char "3"  0x03
		 seg_f,                          // char "4"  0x04
		 seg_a+seg_f+seg_d,              // char "5"  0x05
		 seg_a+seg_f+seg_e+seg_d,        // char "6"  0x06
		 seg_a,                    		 // char "7"  0x07
		 seg_a+seg_f+seg_e+seg_d,  		 // char "8"  0x08
		 seg_a+seg_f+seg_d,        		 // char "9"  0x09
         0                               // char "NLL"  0x16



};

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
static void TIM1723_Write_Cmd(uint8_t cmd);
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);
static void TM1723_Write_Display_TwoData(uint8_t addr,uint8_t dat1,uint8_t dat2);


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
		  
	 }
	 else{
	     TM1723_DIO_SetLow();
		  
	 
	 }
   
   // delay_us(100);
    data =data>>1;//
	 
	 TM1723_CLK_SetHigh();
	 //data =data>>1;//
	//  delay_us(2);
	// data >>=1;//
	
  
     
 }

}
static void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
 
}
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();

}
static void TM1723_Write_Display_TwoData(uint8_t addr,uint8_t dat1,uint8_t dat2)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat1);
   TM1723_Write_OneByte(dat2);
    
   
   TM1723_STB_SetHigh();

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
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);


	TM1723_Write_Display_Data(0xC3,0x01);
	
	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);
	 
	 
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
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC5,0x01);

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);
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
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC2,0x0f);

	 
	

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);
	

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
     TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);
	
	TM1723_Write_Display_Data(0xC2,0x0f);


	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);


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
	 TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC2,0x0f);

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);

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
     TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

     TM1723_Write_Display_Data(0xC2,0x0f);

	//open display
	 TIM1723_Write_Cmd(OpenDispTM1723_5);

}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_Temperature(void)
 	* Function :lcd display 'temperature'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_Temperature(void)
{
     TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

    TM1723_Write_Display_Data(0xC2,lcdNumber_High[0]+0x0F);//display digital "88"

    
    TM1723_Write_Display_Data(0xC3,lcdNumber_Low[0]);//display digital "88"
   
     
	 TM1723_Write_Display_Data(0xC4,0x0);//display "t,c"
     TM1723_Write_Display_Data(0xC5,0x0);//display "t,c"
    
     TM1723_Write_Display_Data(0xC9,0x0);//display digital "88"
     TM1723_Write_Display_Data(0xCA,0x0);//display digital "88"
     
	 TM1723_Write_Display_Data(0xCB,0x0);//display "t,c"
     TM1723_Write_Display_Data(0xCC,0x0);//display "t,c"
    
     TM1723_Write_Display_Data(0xCE,0x0);//display "t,c"
     TM1723_Write_Display_Data(0xCF,0x0);//display "t,c"

	//open display
	 TIM1723_Write_Cmd(0x9B);

}
/*************************************************************************
 	*
 	* Function Name:void Display_Name_Humidity(void)
 	* Function :lcd display 'humidity'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
void Display_Name_Humidity(void)
{

}



