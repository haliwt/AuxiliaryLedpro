#include "singleled.h"
#include "gpio.h"
#include "usart.h"
#include "pwm.h"

led ledab;
static uint8_t BCC_CHECK(void);


void SingleLed_Test(void)
{
    uint8_t temp;
	uint8_t cmdType_0 = aRxBuffer[0]; //command order 1
	uint8_t cmdType_1 = aRxBuffer[1]; //command order 1
	ledab.led_by_a =    aRxBuffer[2];	  //command order 0
	ledab.led_by_b =    aRxBuffer[3];	  //command order 1
	ledab.led_by_c =  aRxBuffer[4]; //command order 1
	ledab.led_by_d =  aRxBuffer[5]; //check sum codes
	uint8_t cmdType_6 = aRxBuffer[6]; //command order 1
	temp = BCC_CHECK();
	HAL_UART_Transmit(&huart1,&temp,1, 2);
	if(cmdType_0 == 0x42){
		if(cmdType_1 == 0x4c){
			if(cmdType_6 == 0xAA)//if(cmdType_6 == temp)
			{
				
				TheFirstGroup_SingleLEDA();
				TheSecondGroup_SingleLEDB();
				TheThirdGroup_SingleLEDC();
				TheFourthGroup_SingleLEDD();
				LR_Control(ledab.led_by_d);
			}
		}
	}
}
  
/*************************************************************************
 	*
	*Function Name: void TheFirstGroup_SingleLEDA(uint8_t ledvala)
	*Function : Turn On LEDAxx LED
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void TheFirstGroup_SingleLEDA(void)
{
        if (ledab.led_by_a > 4)
        {
          TurnOff_TheFirstLedA();
		
		}
        else
        {
            switch (ledab.led_by_a)
            {

			case 0:
				 TurnOff_TheFirstLedA();
				
			break;
			
			case 1:
			    ledab.led_by_b = 0;
			    ledab.led_by_c =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
                TurnOff_TheFirstLedA();
				HAL_Delay(100);
				//1.turn on LEDA1 =1
			    HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
                HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
                
                break;

            case 2:
				ledab.led_by_b = 0;
			    ledab.led_by_c =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
	
				TurnOff_TheFirstLedA();
								HAL_Delay(100);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
                break;

            case 3:
				ledab.led_by_b = 0;
			    ledab.led_by_c =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
				//2. enable
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
                break;

            case 4:
				ledab.led_by_b = 0;
			    ledab.led_by_c =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
			    //2 .EN
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
                break;
			}
        }
}

/*************************************************************************
 	*
	*Function Name: void TheSecondGroup_SingleLEDB(uint_8 ledvalb)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TheSecondGroup_SingleLEDB(void)
{

	if (ledab.led_by_b> 1)
	{
		TurnOff_TheSecondLedB();
			
	}
    else
     {
			switch (ledab.led_by_b)
			{
			case 0:
				 TurnOff_TheSecondLedB();
				
				 break;

            case 1:
				ledab.led_by_a = 0;
			    ledab.led_by_c =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheFirstLedA();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				//1.turn on LEDB1 =1
               
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
                break;

           
			}
        }
 }
/*************************************************************************
 	*
	*Function Name: void TheThirdGroup_SingleLEDC(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
 void TheThirdGroup_SingleLEDC(void)
 {
	if (ledab.led_by_c> 1)
	{
		TurnOff_TheThirdLedC();
			
		}
        else
        {
			switch (ledab.led_by_c)
			{
			case 0:
				  TurnOff_TheThirdLedC();
				  
				 break;

            case 1: //the third group only Pwm control  //PB3 --TIM1-CH2 -AF1
				ledab.led_by_a = 0;
			    ledab.led_by_b =0;
			    ledab.led_by_d =0 ;
				TurnOff_TheSecondLedB();
			    TurnOff_TheFirstLedA();
			    TurnOff_TheFourthLedD();
				HAL_Delay(100);
				TurnOff_TheThirdLedC();
				HAL_Delay(100);
				//1.turn on LEDB1 =1
               
				 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

          
			}
        }
 
 
 }
 /*************************************************************************
 	*
	*Function Name: void TheFourthGroup_SingleLEDD(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TheFourthGroup_SingleLEDD(void)
{
	if (ledab.led_by_d> 4)
	{
		
        TurnOff_TheFourthLedD();		
		}
        else
        {
			switch (ledab.led_by_d)
			{
			case 0:
				TurnOff_TheFourthLedD();
			break;

            case 1:
				ledab.led_by_a = 0;
			    ledab.led_by_b = 0;
			    ledab.led_by_c = 0;
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    HAL_Delay(100);
	            TurnOff_TheFourthLedD();
				HAL_Delay(100);
				//1.turn on LEDB1 =1
                 HAL_GPIO_WritePin(LEDD1_GPIO_Port, LEDD1_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                break;

            case 2:
				ledab.led_by_a = 0;
			    ledab.led_by_b = 0;
			    ledab.led_by_c = 0;
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    HAL_Delay(100);
	            TurnOff_TheFourthLedD();
				HAL_Delay(100);

				//turn on LEDB1
				HAL_GPIO_WritePin(LEDD2_GPIO_Port, LEDD2_Pin, GPIO_PIN_SET);
                HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                break;
			
			  case 3:
				ledab.led_by_a = 0;
			    ledab.led_by_b = 0;
			    ledab.led_by_c = 0;
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    HAL_Delay(100);
	            TurnOff_TheFourthLedD();
				HAL_Delay(100);

				//turn on LEDB1
				HAL_GPIO_WritePin(LEDD3_GPIO_Port, LEDD3_Pin, GPIO_PIN_SET);
                HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                break;
			  
			    case 4:
				ledab.led_by_a = 0;
			    ledab.led_by_b = 0;
			    ledab.led_by_c = 0;
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    HAL_Delay(100);
	            TurnOff_TheFourthLedD();
				HAL_Delay(100);

				//turn on LEDB1
				HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_SET);
                HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                break;
			}
        }
 
}
/*************************************************************************
 	*
	*Function Name:static void FanControl(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void LR_Control(uint8_t fanval)
{
    switch(fanval){
		   
			case 0:  
			
			break;
			
			case 1:
				HAL_GPIO_WritePin( LEDCON_LR_GPIO_Port ,LEDCON_LR_Pin,GPIO_PIN_RESET);
			
			break;
			case 2:
				HAL_GPIO_WritePin( LEDCON_LR_GPIO_Port ,LEDCON_LR_Pin,GPIO_PIN_SET);
			break;
			default :
					
			break;
		
	  }

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheFirstLedA(void)
	*Function : PA2 -> TIM2_CH3
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheFirstLedA(void)
{
     //turn off LEDA LED
	   HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3) ; //HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);//TIM2_CH2
	   HAL_Delay(200);
	   HAL_GPIO_WritePin(GPIOA, LEDA1_Pin | LEDA2_Pin | LEDA3_Pin | LEDA4_Pin , GPIO_PIN_RESET);
      

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheSecondLedB(void)
	*Function : PA15->TIM2_CH1
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheSecondLedB(void)
{
		 //turn off LEDB LED
		 HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);//TIM1_CH2 --PB3//HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
		 HAL_Delay(200);
	
}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheThirdLedC(void)
	*Function : PB3->TIM1-CH2
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheThirdLedC(void)
{
	//turn off LEDC LED
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//TIM1_CH2 --PB3//HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);

}
/*************************************************************************
 	*
	*Function Name:void TunrOff_TheFourthLedD(void)
	*Function : PB4->TIM3_CH1
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheFourthLedD(void)
{
	 //turn off LEDA LED
	  HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ; //HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);//TIM2_CH2
	  HAL_Delay(200);
     HAL_GPIO_WritePin(GPIOA, LEDD1_Pin | LEDD2_Pin | LEDD4_Pin , GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, LEDD3_Pin , GPIO_PIN_RESET);
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
static uint8_t BCC_CHECK(void)
{
   uint8_t i;
	 
	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
	
    for (i = 3; i <6; i++) {
        tembyte = tembyte ^ aRxBuffer[i];
    }
    return tembyte;

}


