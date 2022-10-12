/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

//AI Function GPIO 
/* USER CODE BEGIN Private defines */

#define LCD_BACK_LIGHT_Pin 						GPIO_PIN_9
#define LCD_BACK_LIGHT_GPIO_Port 				GPIOB

#define LCD_POWER_Pin                   		GPIO_PIN_3
#define LCD_POWER_GPIO_Port             		GPIOA

#define LED_POWER_Pin 						GPIO_PIN_6    
#define LED_POWER_GPIO_Port 				GPIOC


#define TM1723_STB_Pin 						GPIO_PIN_4
#define TM1723_STB_GPIO_Port 				GPIOA

#define TM1723_DIO_Pin 						GPIO_PIN_5
#define TM1723_DIO_GPIO_Port 				GPIOA

#define TM1723_SCLK_Pin 					GPIO_PIN_6
#define TM1723_SCLK_GPIO_Port 				GPIOA


//IC VK36N4D  input key

#define TOUCH_KEY_INT_Pin 					GPIO_PIN_2
#define TOUCH_KEY_INT_GPIO_Port 				GPIOA


#define POWER_KEY_Pin                 GPIO_PIN_13      
#define POWER_KEY_GPIO_Port           GPIOB

#define MODE_KEY_Pin                    GPIO_PIN_10
#define MODE_KEY_GPIO_Port              GPIOB

#define DEC_KEY_Pin 					GPIO_PIN_12
#define DEC_KEY_GPIO_Port 				GPIOB

#define ADD_KEY_Pin 					GPIO_PIN_11
#define ADD_KEY_GPIO_Port 				GPIOB










/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

