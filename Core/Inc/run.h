#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"

enum Signal{SINGLE_DATA=1,WIFI_INFO,WIFI_TIME,WIFI_TEMP,WIFI_CMD,WIFI_BEIJING_TIME};

enum State{IDLE ,CODE, RUN};


typedef struct __RUN{

   uint8_t keyValue;
   uint8_t power_key;
   uint8_t gTemperature_timer_flag;
   uint8_t gPower_On;
   uint8_t gRun_flag;
   
   uint8_t keyAdd_continue;
   uint8_t keyDec_continue;
  

   uint8_t gDht11_flag;
   uint8_t gTemperature;
 
   uint8_t gTimer_Counter;
   
  
  
  uint8_t gTimer_setup_zero;

  uint8_t gFan_RunContinue;

  uint8_t temperature_flag;
  
   uint8_t usart_flag;
   uint8_t decodeFlag;
   uint8_t gTemp_check;
   
   uint8_t  gTimer_Cmd;
   uint8_t  gPlasma;
   uint8_t  gPlasma_flag;
   uint8_t  gDry;
   uint8_t  gDry_flag;
   uint8_t  gAi;
  
   uint8_t  gTimes_minutes_temp;
   

   uint8_t  gWifi;
 
   uint8_t  dry_key;
   uint8_t  ster_key;

  

   uint8_t  gTimer_fan_counter;
   uint8_t  gTimer_key_5s;
  
   uint8_t gTimer_key_4s;
   uint8_t gTimer_key_60s;
   uint8_t gTimer_led_500ms;

   uint8_t single_data;
   uint8_t fan_off_60s;
   uint8_t wifi_receive_cmd_flag;
   uint8_t wifi_turn_on;
   uint8_t wifi_turn_off;
   uint8_t wifi_connect_flag;

 
   
   uint8_t gKeyTimer_mode;
   uint8_t dispTime_minute;
   uint8_t Timer_mode_flag;
   uint8_t temperature_set_flag;

   uint8_t gTimer_1hour;
   uint8_t test_flag;
	
  
   
   uint8_t  gTimer_disp_temp;
   uint8_t  gTimer_set_temperature ;
   uint8_t  gTimer_1_hour_counter;
   uint8_t  beijing_time_seconds;
   
   
   uint8_t gReal_humtemp[2];
   uint8_t gInputCmd[2];
   uint8_t wifisetTime[1];
   uint8_t wifiCmd[2];

    int8_t dispTime_hours;
    int8_t 	gTimes_hours_temp;


   
 }RUN_T;

extern RUN_T run_t;



void SplitDispose_Key(uint8_t value);







void Power_Off(void);
void DisplayTimer_Timing(void);

void Wifi_Receive_Cmd(uint8_t cmd);

#endif 



