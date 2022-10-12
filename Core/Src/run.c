#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "display.h"

RUN_T run_t;


void Power_Off(void);





/**********************************************************************
*
*Functin Name: void Wifi_Receive_Cmd(uint8_t cmd)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Wifi_Receive_Cmd(uint8_t cmd)
{
   static uint8_t wifip= 0xff,wifipn = 0xff;
  
      switch(cmd){


		   case 0x80:
		 	
            if(wifip != run_t.wifi_turn_on){
                  wifip = run_t.wifi_turn_on;
              run_t.gTimes_hours_temp=12;
              run_t.gPower_On=1;
          
			  run_t.power_key =1;
			  run_t.gFan_RunContinue=0;
			 
			  run_t.gAi =0; //WT.EDIT 2022.09.01
			  run_t.gPlasma=0;
			  run_t.gDry =0;
			  run_t.gWifi =0;

		      run_t.gPower_On =1;
			 // SendData_PowerOff(1);
			   DisplaySMG_LED();
                run_t.wifi_turn_off ++;
	     
              } 

	         break;

			 case 0x81:
                
				if(wifipn != run_t.wifi_turn_off){
                    wifipn = run_t.wifi_turn_off;
			    run_t.gFan_RunContinue=1;
	            run_t.gPower_On=0;
				run_t.fan_off_60s =0;
	           //  Smg_AllOff();

					run_t.gFan_RunContinue=1; //WT.EDIT 2022.08.31
					run_t.fan_off_60s = 0;
                   //  SendData_PowerOff(0);
					 DisplaySMG_LED();
                    run_t.wifi_turn_on ++;
                }

			 break;

			 case 0x08 : //AI turn on
                 if(run_t.gPower_On ==1){
                    run_t.gAi =0;
                    run_t.gDry =0;
                    run_t.gPlasma = 0;
				   
                 }	

			 break;

			 case 0x18:
                 if(run_t.gPower_On ==1){
			 	   run_t.gAi =1; //turon off AI mode
                 }
             break;

			 case 0x04: //kill turn on
                 if(run_t.gPower_On ==1){
			     run_t.gPlasma = 0;
			     run_t.ster_key =2;
			     run_t.gFan_RunContinue =0;
                 }
			 break;

			 case 0x14: //kill turn off
                 if(run_t.gPower_On ==1){
			 	  run_t.gPlasma =1;
				   run_t.ster_key=1;
				   
				   if(run_t.gDry==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		            }
		            else run_t.gFan_RunContinue =0;
                }
			 break;

			 case 0x02://dry turn on
                 if(run_t.gPower_On ==1){
			        run_t.gDry =0;
					run_t.dry_key =2;
                    run_t.gFan_RunContinue =0;
                 }

			 break;

			 case 0x12:
                 if(run_t.gPower_On ==1){
			 	    run_t.gDry =1;
					run_t.dry_key =1;

				   if( run_t.gPlasma==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		            }
		            else run_t.gFan_RunContinue =0;
			 	}

			 break;


			 default :
                  cmd =0;
			 break;

			 
           }

}

/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Power_Off(void)
{
    	 if(run_t.gPower_On ==0){

			     run_t.gPower_On =0xff;
			 	 // Smg_AllOff();
				
		         run_t.gAi =0;
				
				 run_t.gPlasma=0;
				 run_t.gDry=0;
				
				 run_t.gTemperature =20;
				

				  run_t.gTimer_Cmd=0; //timer of command "1"->timer is start
				  run_t.dispTime_hours=0;
				  run_t.dispTime_minute=0;
				  run_t.gTemperature_timer_flag=0;
			
			
			
				  run_t.gDht11_flag=0; //the first power on display "00"
				  run_t.gTimes_hours_temp=12;
				  run_t.gTimes_minutes_temp=0;
			
				  run_t.gKeyTimer_mode =0;
				  run_t.gTimer_key_5s=0;
				  run_t.gTimer_key_4s=0;
	              run_t.gTimer_key_60s=0;
				  run_t.gTimer_fan_counter=0;
				
				//  SendData_PowerOff(0);//ShutDown_AllFunction();
				  ALL_LED_Off();
				  
                  
		}
		Breath_Led();
		//SMG_POWER_OFF()	;
		
	      //power off display fan run times 60s
          if(run_t.gFan_RunContinue==1){

		      if(run_t.fan_off_60s > 60){
                run_t.gFan_RunContinue=0;
                
              }
			  else{

			   
							
           }

		 }
}

void DisplayTimer_Timing(void)
{
      static uint8_t m,n,p,q;
    
    if(run_t.gTimer_Cmd==1 &&  run_t.temperature_flag !=1){

                
				m = run_t. dispTime_hours /10 ;
			    n=	run_t. dispTime_hours %10; 
				p = run_t. dispTime_minute /10;
				q=  run_t. dispTime_minute %10;
			   // TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"

  }
}
/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function 
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0,tm2;
    
    tm0++;
	//tm1++;
    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		tm2++;
		
		run_t.gTimer_key_4s ++;
		run_t.gTimer_key_60s++;
		run_t.fan_off_60s++;
		 run_t.gTimer_led_500ms =1;
		 run_t.gTimer_key_5s++;
	     run_t.gTimer_disp_temp++;
		 run_t.gTimer_set_temperature++;
		 run_t.beijing_time_seconds++;
	    if(tm2>59){//60s ->1 minute 
	      tm2=0;
		   run_t.gTimer_1_hour_counter++;
		   run_t.gTimer_Counter ++;
		 
		  if(run_t.gTimer_1_hour_counter> 59){ // 1 hour
	        run_t.gTimer_1_hour_counter=0;
			
	         run_t.gTimer_1hour =1;

		  }
		
	    
		}
     

   }
	
}


	
