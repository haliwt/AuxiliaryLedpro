/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * @attention
  * Android auxiliary Board Led cods
  * 
  * 
  *
  ******************************************************************************/
  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
//The first group LED A define
#define LEDAPWM_Pin 				GPIO_PIN_2 //  //PA2 -TIM2_CH3 --AF2
#define LEDAPWM_GPIO_Port 			GPIOA

#define LEDA4_Pin 					GPIO_PIN_3    //PA3
#define LEDA4_GPIO_Port 			GPIOA

#define LEDA3_Pin 					GPIO_PIN_4   //PA4
#define LEDA3_GPIO_Port 			GPIOA

#define LEDA2_Pin 					GPIO_PIN_5  //PA5
#define LEDA2_GPIO_Port 			GPIOA

#define LEDA1_Pin 					GPIO_PIN_6   //PA6--PIN12
#define LEDA1_GPIO_Port 			GPIOA

//The second group led B define 
#define LEDBPWM_Pin 				GPIO_PIN_15   //PA15 --TIM2-CH1-ETR -AF2
#define LEDBPWM_GPIO_Port 			GPIOA

//The third group led  C define 
#define LEDCPWM_Pin 					GPIO_PIN_3  //PB3 --TIM1-CH2 -AF1
#define LEDCPWM_GPIO_Port 				GPIOB

//The fourth group Led D  define
#define LEDDPWM_Pin 					GPIO_PIN_4  //PB4  --TIM3-CH1-AF1
#define LEDDPWM_GPIO_Port 				GPIOB

#define LEDD3_CUT_Pin 				 	GPIO_PIN_0   //PA0
#define LEDD3_CUT_GPIO_Port 		 	GPIOA

#define LEDD4_CUT_Pin 					GPIO_PIN_7   //PA7 ---current increase The fourth group led number 4
#define LEDD4_CUT_GPIO_Port 			GPIOA

#define LEDD2_Pin 						GPIO_PIN_11  //PA11
#define LEDD2_GPIO_Port 				GPIOA

#define LEDD1_Pin 						GPIO_PIN_12  //PA12
#define LEDD1_GPIO_Port 				GPIOA

#define LEDD4_Pin 					    GPIO_PIN_8  //PA8  --
#define LEDD4_GPIO_Port 				GPIOA

#define LEDD3_Pin            		    GPIO_PIN_6  //PC6
#define LEDD3_GPIO_Port       			GPIOC

//To control left board led and right board led 
#define LEDCON_LR_Pin 					GPIO_PIN_5  //PB5
#define LEDCON_LR_GPIO_Port 			GPIOB

/* USER CODE BEGIN Private defines */

void MX_GPIO_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
