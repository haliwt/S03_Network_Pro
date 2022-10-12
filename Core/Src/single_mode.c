#include "single_mode.h"
#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "key.h"
#include "display.h"




void (*single_ai_fun)(uint8_t cmd);
void (*single_add_fun)(void);
void (*single_buzzer_fun)(void);
void (*sendAi_usart_fun)(uint8_t senddat);
void (*dispose_key)(uint8_t dsdat);
static void Setup_Timer_Times(void);
/*******************************************************************************
	 * 
	 * Function Name :void Single_RunMode(void)
	 * Function :main in single run process
	 * Input Reference:No
	 * Return Reference :NO
	 *
*******************************************************************************/
void Single_RunMode(void)
{
   
        if(POWER_KEY_VALUE()  ==KEY_DOWN ){ //power on KEY
          HAL_Delay(10);
		 while(POWER_KEY_VALUE()  ==KEY_DOWN);

        run_t.keyValue= 0x80;
		dispose_key(run_t.keyValue);// key handler 

	
			    if(run_t.gPower_On == 1){
			         SendData_PowerOff(1);
					 run_t.test_flag ++;
			     }
				else{
					
					SendData_PowerOff(0);
					run_t.gFan_RunContinue=1; //WT.EDIT 2022.08.31
					run_t.fan_off_60s = 0;
					run_t.wifi_turn_on++; 
				}
			
			DisplaySMG_LED();
         
		
         
     }
     else if(MODE_KEY_VALUE()==KEY_DOWN){ //Mode key 
	 	    
	     	 HAL_Delay(10);
	         while(MODE_KEY_VALUE()==KEY_DOWN);
	 	  
			run_t.keyValue= 0x40;
			dispose_key(run_t.keyValue);//displaySmg_led_fun(run_t.keyValue);//Display_Smg_RunMode(run_t.keyValue );
			single_add_fun();//DisplayTiming_KEY_Add_Subtract_Fun();
			single_buzzer_fun();//SendData_Buzzer();
		
		
		  
     }
     else if(DEC_KEY_VALUE()==KEY_DOWN){ //"-" KEY
	 	
		  HAL_Delay(10);
	 	if(DEC_KEY_VALUE()==KEY_DOWN);
			  
	          run_t.keyValue= 0x20; //
	          dispose_key(run_t.keyValue);//Display_Smg_RunMode(run_t.keyValue );
	        
		      single_buzzer_fun();//SendData_Buzzer();
	          single_add_fun();//DisplayTiming_KEY_Add_Subtract_Fun();
	          
			 
		  
		 
	}
     else if(ADD_KEY_VALUE()==KEY_DOWN){ //"+" KEY
	 	 HAL_Delay(10);

		  if(ADD_KEY_VALUE()==KEY_DOWN);
		  	 
	     	  run_t.keyValue= 0x10;
	          dispose_key(run_t.keyValue);//Display_Smg_RunMode(run_t.keyValue );
		      single_buzzer_fun();//SendData_Buzzer();
	          single_add_fun();//DisplayTiming_KEY_Add_Subtract_Fun();
			
	}
	
     else{
	 	 
	 	
         RunReference_Fun();
     }
	 
  }
/*******************************************************************************
	 * 
	 * Function Name :void RunReference_Fun(void)
	 * Function :single run process
	 * Input Reference:No
	 * Return Reference :NO
	 *
*******************************************************************************/
void RunReference_Fun(void)
{

    uint8_t tim0;
    if(run_t.gPower_On ==1){
	    panel_led_fun();

	 if(run_t.gTimer_key_5s >4 && (run_t.gKeyTimer_mode ==1)){	//timer timing set up 
        run_t.gTimer_key_5s =0;
		run_t.gKeyTimer_mode =0;
	    run_t.Timer_mode_flag=0;
		
		
	
		 if(run_t.dispTime_hours >0){ //be sure definite time 
		      run_t.gTimer_Cmd=1;	  //timer is times start  
		      run_t.dispTime_minute =0;
		      run_t.gTimer_setup_zero =0;
		      run_t.gTimer_Counter=0;
			  run_t.gTimer_1_hour_counter=0;
			
			 SendData_Set_Timer(run_t.dispTime_hours);
			  
         }
		 else{ //cancel definite time
		 	run_t.dispTime_hours=0;
		    run_t.gTimer_Cmd=0;
		    run_t.gTimer_setup_zero=0;
			run_t.dispTime_minute=0;
			run_t.gTimer_Counter=0;
			// run_t.gTimes_minutes_temp=0;
			
			
        }

		
	}
    //set up temperature be done 
    if(run_t.gTimer_set_temperature > 4 && run_t.temperature_set_flag == 1){
          
	       run_t.temperature_set_flag =0; 
		   run_t.gTemperature_timer_flag =1;
		   run_t.Timer_mode_flag =0;
		   SendData_Set_Temperature(run_t.gTemperature);
	
    }

	
    /******************timer timing *****************************/
    Setup_Timer_Times();

	
    /*-----------------display temperature and humidity------------------*/
	if(run_t.gTimer_key_4s > 19 || tim0< 30){

         tim0 ++ ;
		 run_t.gTimer_key_4s=0;

	      //single_add_fun();//DisplayTiming_KEY_Add_Subtract_Fun();
		
         /// Display_DHT11_Value();
          if(run_t.gTimer_Cmd ==1)DisplayTimer_Timing();
          else 
              single_add_fun();

		  if(tim0> 30 ) tim0 = 31;

	}
	 
    
	 //wifi led indicator light
      if(run_t.wifi_connect_flag == 0 && run_t.gWifi ==0){
	 	
		 
		if(run_t.gTimer_led_500ms ==1){
			run_t.gTimer_led_500ms =0;
			//LED_WIFI_Toggle();
			sendAi_usart_fun(0x01);//S
         }
        else{
             Display_DHT11_Value();
        
        }
         
		 
	 }
	 else if(run_t.gWifi == 0){

		//LED_WIFI_ON();

	}
	else{
	   // LED_WIFI_OFF();


	}
     
 
	 /*Temperature -> auto shut off machine be checked interval 60s */
	 if(run_t.gTemperature_timer_flag ==1 && run_t.gTimer_key_60s >59 ){
            run_t.gTimer_key_60s=0;
		 
		  
		  if(run_t.gTemperature <=run_t.gReal_humtemp[1] || run_t.gReal_humtemp[1] >=40){//envirment temperature
	  
				  
				   run_t.gAi = 1;
			  
				   run_t.gPlasma =1;
				   run_t.gDry =1;
				  
				  // AI_Auto_Stop();
				   sendAi_usart_fun(0x87);//SendData_AI(0X81); //turn off AI 
		  }
		  else if((run_t.gTemperature -3) >= run_t.gReal_humtemp[1] || 37 >= run_t.gReal_humtemp[1]){
	  
				  run_t.gAi = 0;
			   
				 run_t.gPlasma =0;
				 run_t.gDry =0;
		  
				 panel_led_fun();//Display_Function_OnOff();
	  
				 sendAi_usart_fun(0x88);//SendData_AI(0X71); //turn on AI 
				 
		  }
	  
	  }
		

      /*-------------poer off turn off fan continuce run 60s----------------*/
	  //fan continuce run 60s ,the all function turn off 
       if(run_t.gFan_RunContinue==1){
            
          if(run_t.fan_off_60s > 60){ 
		       run_t.gFan_RunContinue++;
			  // LED_AI_OFF();
           }
		   else{

			 //LED_AI_ON();
							
           }
       }

	
  }
}
	


/******************************************************************************
*
*Function Name:static void Setup_Timer_Times(void)
*Funcion:display setup timer times  //__asm("NOP");//等待1个指令周期，系统主频24M
*Iinput Ref:NO
*Return Ref:NO
*
******************************************************************************/
static void Setup_Timer_Times(void)
{
    
	static uint8_t minute_flag=0,tf_flag,send_times;
	if(run_t.gTimer_Cmd==1){
		
        
       if(run_t.gTimer_Counter > 0){

	    run_t.gTimer_Counter =0;
		send_times ++ ;
	   	
         if( run_t.gTimer_1hour==1){ // 1 hour

			run_t.gTimer_setup_zero=0;
			run_t.gTimer_1hour=0;
		    minute_flag=0;
         }

		if(run_t.gTimer_setup_zero==0){
			run_t.gTimer_setup_zero++;
			
		    run_t.dispTime_hours -- ;
		
			run_t.dispTime_minute =59;

		    SendData_Timer_Hours((run_t.dispTime_hours +1));
           

			if(run_t.dispTime_hours < 0 ){

	            run_t.dispTime_hours=0;
			
				run_t.dispTime_minute=0;
				run_t.gTimer_Cmd =0;	 //shut off timer of times

			
				run_t.gPower_On =0 ;
				//sendData 
				SendData_Timer_Hours(0xff);
				
				SendData_PowerOff(0);//shut down 
				//Power_Off();
			}

			tf_flag = 1;

		}


		if(tf_flag==1){

		   tf_flag++;
		   
		}
		else{

		 run_t.dispTime_minute=59 - minute_flag;
		
		}
	  
	   minute_flag++;
	   if(send_times ==5){
           send_times = 0;
		   //send timer timing to smart phone APP


	   }

	  }
    }
    else{ //short times for key


            if(run_t.beijing_time_seconds > 59){
				run_t.beijing_time_seconds=0;
				run_t.gTimes_minutes_temp++;
                if(run_t.gTimes_minutes_temp > 59){ //1 hour
                    run_t.gTimes_minutes_temp=0;
                    run_t.gTimes_hours_temp++;
                   if(run_t.gTimes_hours_temp > 24){
				    run_t.gTimes_hours_temp =0;
				    }
			   }
               Display_GMT();
		      }
         }

}
   

/******************************************************************************
*
*Function Name:void Single_RunCmd(void)
*Funcion: handle of receive by usart data
*
*
******************************************************************************/
void Single_RunCmd(void)
{
   if(run_t.gPower_On ==1 ){
        Decode_Function();

     }
    
   if(run_t.gWifi ==0) //wifi function turn 0n 
        Wifi_Receive_Cmd(run_t.wifiCmd[0]);

    if(run_t.gPower_On ==0 || run_t.gPower_On == 0xff){
	 	
	      Breath_Led();
		  Power_Off();
     }
    


}

/****************************************************************
 * 
 * Function Name:
 * Function :function of pointer 
 * 
 * 
****************************************************************/
void Single_Add_RunCmd(void(*addHandler)(void))
{
    single_add_fun = addHandler;   

}

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void))
{
	single_buzzer_fun = buzzerHandler;

}
void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat))
{
    sendAi_usart_fun = sendaiHandler;

}

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat))
{

  dispose_key = keyHandler;

}


