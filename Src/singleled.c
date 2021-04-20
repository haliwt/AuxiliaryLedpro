#include "singleled.h"
#include "gpio.h"
#include "usart.h"
#include "pwm.h"

led ledab;
static uint8_t BCC_CHECK(void);
static void RedLed_Off(void);
static void GreenLed_Off(void);
static void BlueLed_Off(void);

static uint8_t ReadLR_Control(void) ;
/*************************************************************************
 	*
	*Function Name: void SingleLed_Test(void)
	*Function : all function be test
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void SingleLed_Test(void)
{
    uint8_t temp;
	uint8_t cmdType_0 = aRxBuffer[0]; //command order 1
	uint8_t cmdType_1 = aRxBuffer[1]; //command order 1
	//uint8_t cmdType_2 = aRxBuffer[2];	  //led turn on or off command --main board 
	//uint8_t cmdType_3 = aRxBuffer[3];	  //led turn on or off command --main board 
	ledab.led_by_cd = aRxBuffer[4]; //led turn on or off command --need 
	//ledab.led_by_d= aRxBuffer[5]; //led turn on or off command --need 
	uint8_t cmdType_6 = aRxBuffer[6]; //BCC by check sum
	temp = BCC_CHECK();
	HAL_UART_Transmit(&huart1,&temp,1, 2);
	if(cmdType_0 == 0x42){
		if(cmdType_1 == 0x4c){
			if(cmdType_6 == temp)//if(cmdType_6 == temp)
			{
				
				ledab.runstep =1;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TheFirstGroup_SingleLEDA();
				TheSecondGroup_SingleLEDB();
				TheThirdGroup_SingleLEDC();
				TheFourthGroup_SingleLEDD();
				//compound mode
				RedGreenBlue_LED_Com();
				 
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
        if (ledab.led_by_cd > 0x14 && ReadLR_Control() == 1)
        {
          TurnOff_TheFirstLedA();
		
		}
        else if(ReadLR_Control() == 1)
        {
            switch (ledab.led_by_cd)
            {

			case 0:
				 TurnOff_TheFirstLedA();
				 ledab.runstep =0x10;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
			break;
			
			case 0x11:
			     ledab.runstep =0x11;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
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

            case 0x12:
			     ledab.runstep =0x12;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
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

            case 0x13:
			     ledab.runstep =0x13;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
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

            case 0x14:
				ledab.runstep =0x14;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
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
	*Function : color green led
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TheSecondGroup_SingleLEDB(void)
{

	if (ledab.led_by_cd > 0x21 && ReadLR_Control() == 1)
	{
		TurnOff_TheSecondLedB();
			
	}
    else if(ReadLR_Control() == 1)
     {
			switch (ledab.led_by_cd)
			{
			case 0:
				 TurnOff_TheSecondLedB();
				
				 break;
			case 0x20:
				 TurnOff_TheSecondLedB();
			break;

            case 0x21:
                TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
			    TurnOff_TheFirstLedA();
				HAL_Delay(100);
				
				HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //TIM2_CH1 the second group
			    //PA15-22PIN--the second group pwm ----Green
                break;
			default:
				 TurnOff_TheSecondLedB();
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
	if (ledab.led_by_cd > 0x31 && ReadLR_Control() == 1)
	{
		TurnOff_TheThirdLedC();
			
	}
    else if(ReadLR_Control() == 1)
    {
			switch (ledab.led_by_cd)
			{
			case 0:
				  TurnOff_TheThirdLedC();
				  
				 break;

            case 0x30:
				TurnOff_TheThirdLedC();
				
			break;
			
			
			case 0x31: //the third group only Pwm control  //PB3 --TIM1-CH2 -AF1
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
			    TurnOff_TheFirstLedA();
				HAL_Delay(100);
			    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2 PB3 the third group
			     //PB3-23PIN --the third gropu pwm ---Blue
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
	if (ledab.led_by_cd > 0x44 && ReadLR_Control() == 1)
	{
		
        TurnOff_TheFourthLedD();		
     }
    else if(ReadLR_Control() == 1)
    {
			switch (ledab.led_by_cd)
			{
			case 0:
				TurnOff_TheFourthLedD();
			break;

			case 40:
				TurnOff_TheFourthLedD();
				ledab.runstep =0x40;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);

			break;

      case 0x41:
					 ledab.runstep =0x41;
				  HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
			    TurnOff_TheFourthLedD();
				  TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	      
				   HAL_Delay(100);
				//1.turn on LEDB1 =1
         HAL_GPIO_WritePin(LEDD1_GPIO_Port, LEDD1_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
				// HAL_Delay(100);
			  
                break;

            case 0x42:
				ledab.runstep =0x42;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				 TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	        
				HAL_Delay(100);

				//turn on LEDB1
				HAL_GPIO_WritePin(LEDD2_GPIO_Port, LEDD2_Pin, GPIO_PIN_SET);
        HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
				//HAL_Delay(100);
				
		
                break;
			
			  case 0x43:
				ledab.runstep =0x43;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				 TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	       
				HAL_Delay(100);

				//turn on LEDB1
				HAL_GPIO_WritePin(LEDD3_GPIO_Port, LEDD3_Pin, GPIO_PIN_SET);
        HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
				//HAL_Delay(100);
				
			
                break;
			  
			    case 0x44:
				ledab.runstep =0x44;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
			  TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
			  TurnOff_TheSecondLedB();
			  TurnOff_TheThirdLedC();
	        
				HAL_Delay(100);
        //turn on LEDB1
				HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_SET);
        HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
			//	HAL_Delay(100);
			  
         break;
					default:
						
					break;
			}
        }
 
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
	    if(tempVal == GPIO_PIN_RESET ) 
			return 0;
		else return 1;
	  

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
  
	 
	 uint8_t tembyte =0xAA ^ aRxBuffer[4];
	 
   //  tembyte = tembyte ^ aRxBuffer[5];
    
    return tembyte;

}
/*************************************************************************
 	*
	*Function Name:void RedLed(void)
	*Function : color red led
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void RedLed(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;  //PB4 -PIN24 --the fourth group pwm
	HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_SET);

}

static void RedLed_Off(void)
{
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ;  //PB4 -PIN24 --the fourth group pwm
	HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_RESET);

}
/*************************************************************************
 	*
	*Function Name:void GreenLed(void)
	*Function : color green led
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void GreenLed(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//PA15-22PIN--the second group pwm ----Green

}

static void GreenLed_Off(void)
{
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);//PA15-22PIN--the second group pwm ----Green

}
/*************************************************************************
 	*
	*Function Name:void BlueLed(void)
	*Function : color blue led
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void BlueLed(void)
{
   HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);  //PB3-23PIN --the third gropu pwm ---Blue

}

static void BlueLed_Off()
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);  //PB3-23PIN --the third gropu pwm ---Blue

}
/*************************************************************************
 	*
	*Function Name:void RedGreenBlue_LED_Com(void)
	*Function : compound order
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void RedGreenBlue_LED_Com(void)
{
	if (ledab.led_by_cd > 0x56 && ReadLR_Control() == 1)
	{
		TurnOff_TheFirstLedA();
		TurnOff_TheSecondLedB();
		TurnOff_TheThirdLedC();
		TurnOff_TheFourthLedD();		
     }
    else if(ReadLR_Control() == 1)
	{
	     switch(ledab.led_by_cd){
		 
			 case 0:
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	            TurnOff_TheFourthLedD();
			    ledab.led_blue=0;
			    ledab.led_red =0;
			    ledab.led_green =0;
				 
			 break;
			 case 0x50:
			 	TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	            TurnOff_TheFourthLedD();
			    ledab.led_blue=0;
			    ledab.led_red =0;
			    ledab.led_green =0;

			 break;
			 
			 case 0x51:
				ledab.runstep =0x51;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	            TurnOff_TheFourthLedD();
			    HAL_Delay(100);
			 
				 ledab.led_red =1;
				 RedLed();
			 
			     if(ledab.led_green ==1)
			     GreenLed();
			 
				if(ledab.led_blue ==1)
				 BlueLed();
				 
			 break;

			 case 0x52: //turn off red led 
                ledab.led_red =0 ;
				RedLed_Off();
				if(ledab.led_green ==1)
			     GreenLed();
			 
				if(ledab.led_blue ==1)
				 BlueLed();

			 break;
			 
			 case 0x53 :
				ledab.runstep =0x53;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	            TurnOff_TheFourthLedD();
			    HAL_Delay(100);
			     ledab.led_green =1;
			     GreenLed();
			 
				if(ledab.led_red ==1)
				 RedLed();
				
				if(ledab.led_blue ==1)
				BlueLed();
				 
			 break;
			 case 0x54:  //turn off GreenLed OFF
			     ledab.led_green =0;
				 GreenLed_Off();
				 if(ledab.led_red ==1)
				 RedLed();
				
				if(ledab.led_blue ==1)
				BlueLed();

			 break;
			
		     case 0x55:
				ledab.runstep =0x55;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheFirstLedA();
			    TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
	            TurnOff_TheFourthLedD();
			    HAL_Delay(100);
			    ledab.led_blue =1;
			    BlueLed();
			 
			    if(ledab.led_green ==1)
			     GreenLed();
			 
				if(ledab.led_red ==1)
				 RedLed();
				 
			  break;
			  case 0x56:
				ledab.led_blue =0;
				BlueLed_Off();
				 if(ledab.led_green ==1)
			     GreenLed();
			 
				if(ledab.led_red ==1)
				 RedLed();

			  break;
		 
		 
		 
		 }
	
	
	}
    


}

