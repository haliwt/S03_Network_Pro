#ifndef __LED_H_
#define __LED_H_
#include "main.h"





#define LED_POWER_ON()				HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin,GPIO_PIN_SET)
#define LED_POWER_OFF()             HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin,GPIO_PIN_RESET)




extern void (*panel_led_fun)(void);


void Breath_Led(void);



void ALL_LED_Off(void);






#endif 
