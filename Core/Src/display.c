#include "display.h"
#include "smg.h"
#include "cmd_link.h"
#include "run.h"
#include "key.h"
#include "led.h"
#include "single_mode.h"


/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void DisplaySMG_LED(void)
{
   static uint8_t m,n,p,q;
    if(run_t.gPower_On==1){

		//SMG_POWER_ON()	;


		m = (run_t.gTimes_hours_temp /10) ;
		n=	(run_t.gTimes_hours_temp%10); 
		p = (run_t.gTimes_minutes_temp /10);
		q=  (run_t.gTimes_minutes_temp %10);



		//TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"
		panel_led_fun();//Display_Function_OnOff();
		//KeyLed_Power_On();

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
void Display_DHT11_Value(void)
{
    
  static uint8_t hum1,hum2,time[1],temp[1]; 
  static uint8_t m,n,p,q,temp1,temp2;
 

    switch(run_t.single_data){
    
       case SINGLE_DATA:
	   	run_t.single_data=0;
    
        hum1 =  run_t.gReal_humtemp[0]/10 %10;  //Humidity 
        hum2 =  run_t.gReal_humtemp[0]%10;
        
        temp1 = run_t.gReal_humtemp[1]/10 %10;  // temperature
        temp2 = run_t.gReal_humtemp[1]%10;

      // TM1639_Write_2bit_TempData(temp1,temp2);
      // TM1639_Write_2bit_HumData(hum1,hum2);
      break;

      case WIFI_INFO:

//	    if(run_t.gWifi ==0 ){
//			run_t.single_data=0;
//
//        if(run_t.gInputCmd[0] == 0x55 && run_t.gInputCmd[1]==0xaa){
//             run_t.wifi_connect_flag =1;
//
//	    } 
//	    else if(run_t.gInputCmd[0] == 0x55 && run_t.gInputCmd[1]==0x00){
//	    	   run_t.wifi_connect_flag = 0;
//	    }
//	   }
      break;

      case WIFI_TIME: //time and temperature
          if((run_t.wifi_connect_flag ==1) && (run_t.gWifi ==0)){
		  	run_t.single_data=0;
		  	
          if(run_t.gInputCmd[0] > 0){


		     if(time[0] != run_t.gInputCmd[0]){

			      time[0] = run_t.gInputCmd[0];

	             
	               run_t.wifisetTime[0]= run_t.gInputCmd[0];
			        run_t.dispTime_hours=run_t.wifisetTime[0];
			 
			       run_t.dispTime_minute = 0;

	              run_t.gTimer_Cmd=1;	 
			    
			      run_t.gTimer_setup_zero=0;
			      //run_t.gTimer_Counter=0;
		       	}
			}
          else{
          
           run_t.gTimer_Cmd=0;	
           run_t.dispTime_minute = 0;
           run_t.dispTime_hours=0;
          
          }

		        m = run_t. dispTime_hours /10%10 ;
			    n=	run_t. dispTime_hours %10; 
	            if(run_t.dispTime_minute ==0 ){ 
					p=0;
					q=0;

	            }
				else{
				   p = run_t. dispTime_minute /10 %10;
				   q=  run_t. dispTime_minute %10;
				}
			    //TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"
           
        } 

      break;
         
      case  WIFI_TEMP:
           if((run_t.wifi_connect_flag ==1) && (run_t.gWifi ==0)){
		   	run_t.single_data=0;
           if(run_t.gInputCmd[0] >19 && run_t.gInputCmd[0] <41){ //setup temperature 

		        if(temp[0] !=run_t.gInputCmd[0]){
				    temp[0]  =run_t.gInputCmd[0];

				 run_t.temperature_set_flag=1;
	       	     run_t.gTemperature = run_t.gInputCmd[0];

		        }
                
             }

		   	      temp1 = run_t.gTemperature/10 %10;
	              temp2 = run_t.gTemperature%10;
					    
				 //  TM1639_Write_4Bit_TemperatureData(temp1,temp2); //WT.EDIT 2022.09.01
                    
         }
      break;

	  
     
         
    
      default:
         run_t.single_data=0;
      	
      break;



  }
}  


/**********************************************************************
*
*Functin Name: void DisplayTiming_KEY_Add_Subtract_Fun(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void DisplayTiming_KEY_Add_Subtract_Fun(void)
{
      
	  static uint8_t m,n,p,q,temp1,temp2;

	if(run_t.gPower_On==1){
    
    if(run_t.gKeyTimer_mode==1){ // set uP timer of  timimg 
		
            run_t.Timer_mode_flag =1;
			m = run_t.dispTime_hours /10%10;
			n=	run_t.dispTime_hours %10;
		
	      // TM1639_Write_4Bit_Data(0,0,m,n,1) ; // timer   mode  "H0: xx"
		
	 }
	
	//display set up time timing 		
     if(run_t.gTimer_Cmd==1 &&  run_t.temperature_flag ==0 && run_t.temperature_set_flag !=1 && run_t.Timer_mode_flag ==0 ){

                
				m = run_t. dispTime_hours /10%10 ;
			    n=	run_t. dispTime_hours %10; 
	            if(run_t.dispTime_minute ==0 ){ 
					p=0;
					q=0;

	            }
				else{
				   p = run_t. dispTime_minute /10 %10;
				   q=  run_t. dispTime_minute %10;
				}
			  //  TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"

	}
	else{

    if(run_t.gTimer_Cmd==0 &&  run_t.Timer_mode_flag !=1  && run_t.temperature_set_flag !=1){ //display normal times don't edit  timer of times 

                       
						m = run_t.gTimes_hours_temp /10 %10;
					    n=	run_t.gTimes_hours_temp%10; 
						p = run_t.gTimes_minutes_temp /10 %10;
						q=  run_t.gTimes_minutes_temp %10;
						//TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"
				
	}
    else if(run_t.Timer_mode_flag !=1 ||  run_t.temperature_set_flag  ==1){ //Temperature of setup auto shut off machine
						
						temp1 = run_t.gTemperature/10 %10;
	                     temp2 = run_t.gTemperature%10;
					    
				//	TM1639_Write_4Bit_TemperatureData(temp1,temp2); //WT.EDIT 2022.09.01
                    run_t.temperature_flag =0;
	 }
    }  
	}
}

void Display_GMT(void)
{ 
    static uint8_t m,n,p,q;
	m = run_t.gTimes_hours_temp /10 %10;
	n=	run_t.gTimes_hours_temp%10; 
	p = run_t.gTimes_minutes_temp /10 %10;
	q=  run_t.gTimes_minutes_temp %10;
	//TM1639_Write_4Bit_Data(m,n,p,q,0) ; //timer is default 12 hours "12:00"


}


