/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

   GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIOC pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LEDD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIOA pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LEDAPWM_Pin|LEDA1_Pin|LEDA2_Pin|LEDD4_CUT_Pin|LEDD2_Pin|LEDD1_Pin
                          |LEDA3_Pin|LEDA4_Pin|LEDBPWM_Pin|LEDD3_CUT_Pin|LEDD4_Pin
                          , GPIO_PIN_RESET);

  /*Configure GPIOB pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LEDCPWM_Pin|LEDDPWM_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LEDD2_EN_Pin, GPIO_PIN_SET); //UV control EN pin
   
   //GPIO Initinal 
  /*Configure GPIOC pin : LEDD3_Pin */
  GPIO_InitStruct.Pin = LEDD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LEDD3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIOA pins : LEDACUT_Pin LEDAPWM_Pin LEDA2_Pin LEDA3_Pin
                           LEDA4_Pin LEDA5_Pin LEDA6_Pin FAN_Pin
                           LEDB1_Pin LEDB2_Pin LEDB3_Pin */
													 
  GPIO_InitStruct.Pin = LEDAPWM_Pin|LEDA1_Pin|LEDA2_Pin|LEDD4_CUT_Pin|LEDD2_Pin|LEDD1_Pin
                          |LEDA3_Pin|LEDA4_Pin|LEDBPWM_Pin|LEDD3_CUT_Pin|LEDD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /*Configure GPIOB pins : LEDA7_Pin LEDA8_Pin LEDBPWM_Pin LEDB4_Pin
                           LEDB5_Pin LEDB6_Pin LEDB7_Pin */
  GPIO_InitStruct.Pin = LEDCPWM_Pin|LEDDPWM_Pin|LEDD2_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  
  //Configure GPIOB PB5,PB0 INPUT pins--
  GPIO_InitStruct.Pin = LEDCON_LR_Pin| GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLDOWN;//GPIO_NOPULL;
  //GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LEDCON_LR_GPIO_Port, &GPIO_InitStruct);
  

 
  //USART AFx Function Define GPIO
  /*Configure GPIO pin : PB7  --AF0 USART1 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;//GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;//GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/*************************************************************************
 	*
	*Function Name:uint8_t  ReadLR_Control(void);
	*Function : 
	*Input Ref: NO
	*Return Ref: 10 --left led on  01 --right led on
	*
******************************************************************************/
uint8_t  ReadLR_Control(void)
{
        uint8_t tempVal;
		tempVal = HAL_GPIO_ReadPin(LEDCON_LR_GPIO_Port,LEDCON_LR_Pin);
	    if(tempVal == 0 ) return 0;
		else if(tempVal == 1) return 1;
	  

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
