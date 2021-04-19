/* USER CODE BEGIN Header */
/***************************************************************************//**
  �ļ�: main.c
  Function: singleLed be Hardware test
  �汾: V1.0.0
  ʱ��: 20210413
	Hardware IC: stm32g031g8Ux
*******************************************************************************/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "singleled.h"
#include "pwm.h"


void SystemClock_Config(void);

/* USER CODE BEGIN 0 */
uint8_t aTxBuffer[RXBUFFERSIZE] ;
	#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
//	#define TXBUFFERSIZE                    3 //(COUNTOF(aTxBuffer)) //(COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
//#define RXBUFFERSIZE                    7 //TXBUFFERSIZE
uint8_t aRxBuffer[RXBUFFERSIZE];
	__IO ITStatus UartReady = RESET;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  
  
	HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();


  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	MX_TIM2_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/* USER CODE END WHILE */
	//	if (HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
		{
		  //Error_Handler();
		}
		//else
		{
			
			//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//PA15-22PIN--OK
			
			//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3); //PA2-8PIN
			
		//	TurnOff_TheSecondLedB();
			   // TurnOff_TheThirdLedC();
			   // TurnOff_TheFourthLedD();
			//	HAL_Delay(100);
              //  TurnOff_TheFirstLedA();
				HAL_Delay(100);
				//1.turn on LEDA1 =1
			    HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
			   //2.EN on
                HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ; //PA2
			
			//HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;  //PB4 -PIN24
		  // SingleLed_Test() ; //TestMode
		
		//if (HAL_UART_Transmit_IT(&huart1, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
		//{
			//UartReady = RESET;
			
		// Error_Handler();
		//}
		//CheckRun();
		}
				
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks 
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
