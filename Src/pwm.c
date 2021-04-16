#include "pwm.h"
#include "main.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/*************************************************************************************
*	*
*Function Name:void MX_TIM1_Init(void)
*Function:Timer 1 define and frequency set PB3->TIM1_CH2-AF1
*
*	
**************************************************************************************/
void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 4-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100 -1 ;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 80; //pwm duty cycle 50%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) //PB3 TIM1_CH2
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim1);

}
/*************************************************************************************
*	*
*Function Name:void MX_TIM2_Init(void)
*Function:Timer 2 define and frequency set  PA15 --> TIM2_CH1-ETR, PA2->TIM2_CH3
*
*	
**************************************************************************************/
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC_1 = {0}; //PA15 -TIM2_CH1
  TIM_OC_InitTypeDef sConfigOC_3 = {0}; //PA2  -TIM2_CH3
  
  htim2.Instance =TIM2 ; 
  htim2.Init.Prescaler = 4-1; //ck_cnt = 16MHz /(PSC + 1)
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100 -1 ; //Fpwm = ck_cnt / Period = 
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  //PA15 TIM2_CH1
  sConfigOC_1.OCMode = TIM_OCMODE_PWM1;
  sConfigOC_1.Pulse = 80;  //pwm duty cycle 80%
  sConfigOC_1.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC_1.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC_1, TIM_CHANNEL_1) != HAL_OK)// TIM_CHANNEL_1 to TIM_CHANNEL_2 PA1 ---> TIM2_CH2
  {
    Error_Handler();
  }
  //PA2 TIM2_CH3
  sConfigOC_3.OCMode = TIM_OCMODE_PWM1;
  sConfigOC_3.Pulse = 80;  //pwm duty cycle 80%
  sConfigOC_3.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC_3.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC_3, TIM_CHANNEL_3) != HAL_OK)// TIM_CHANNEL_1 to TIM_CHANNEL_2 PA1 ---> TIM2_CH2
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim2);

}
/*************************************************************************************
*	*
*Function Name:void MX_TIM3_Init(void)
*Function:Timer 3 define and frequency set  PB4------> TIM3_CH1--AF1 
*
*	
**************************************************************************************/
void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance =TIM3;
  htim3.Init.Prescaler = 4-1; //ck_cnt = 16MHz /(PSC + 1)
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100 -1 ; //Fpwm = ck_cnt / Period = 
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 80;  //pwm duty cycle 80%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)// TIM_CHANNEL_1 to TIM_CHANNEL_2 PA1 ---> TIM2_CH2
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim3);

}
/**************************************************************************************
***
*Function Name:void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
*Function :special MCU initianl function, must to connector MCU process user edit cods
*
*
*
**************************************************************************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM2) //TIM3 to TIM2 WT.EDIT 2021.04.15
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();//__HAL_RCC_TIM3_CLK_ENABLE(); //WT.EDIT 
	HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);    //HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0); //WT.EDIT 
    HAL_NVIC_EnableIRQ(TIM3_IRQn);   //HAL_NVIC_EnableIRQ(TIM3_IRQn);

   
  }
   else if(tim_baseHandle->Instance==TIM3){
      
	    __HAL_RCC_TIM3_CLK_ENABLE(); //WT.EDIT 
	    /* TIM3 interrupt Init */
        HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0);    //HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0); //WT.EDIT 
        HAL_NVIC_EnableIRQ(TIM3_IRQn);   //HAL_NVIC_EnableIRQ(TIM3_IRQn);
  
   
   }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */
    //__HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM1 GPIO Configuration    
	PB3     ------> TIM1_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3; 
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }
  else if(timHandle->Instance==TIM2)// PA15 -TIM2_CH1-ETR PA2->TIM2_CH3
  {
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration    
    PA15    ------> TIM2_CH1-ETR
	PA2     ------> TIM2_CH3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate =GPIO_AF2_TIM2; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  }
  else if(timHandle ->Instance == TIM3){  //PB4 TIM3_CH1-AF1
  
		__HAL_RCC_GPIOB_CLK_ENABLE();
	  /**TIM3 GPIO Configuration    
    PB4     ------> TIM3_CH1 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate =GPIO_AF1_TIM3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM2)// TIM3 to TIM2
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();//__HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);//HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
   else if(tim_baseHandle->Instance==TIM3)// TIM3 to TIM2
   {
		 __HAL_RCC_TIM3_CLK_DISABLE();//__HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
      HAL_NVIC_DisableIRQ(TIM3_IRQn);//HAL_NVIC_DisableIRQ(TIM3_IRQn);
   
   }
} 
