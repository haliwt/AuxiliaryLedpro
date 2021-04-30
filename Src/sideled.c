#include "sideled.h"
#include "gpio.h"
#include "singleled.h"
#include "usart.h"
#include "pwm.h"


#define MAX_CMD_PARA_SIZE    8
#define BOARD_ADDR	76	// 'L'

#define STATE_PREAMBLE1	0	// 'M'	fixed
#define STATE_PREAMBLE2	1	// 'X'	fixed
#define STATE_ADDR		2	// 'L' this board
#define STATE_CMD		3	// 'S' led select command
#define STATE_SIZE		4	// length of command parameter
#define STATE_PARA		5	// parameter
#define STATE_CRC		6	// checksum


uint8_t inputCmd[BUFFER_SIZE];
//static uint8_t transBack;

//static uint8_t cmd;
static uint8_t  classID[3];
static uint8_t state;
static uint8_t decodeFlag;

static uint8_t cmdSize;
static uint8_t paraIndex;
static uint8_t crcCheck;


static uint8_t hasLedOn_linear;
static uint8_t hasLedOn_spot;
static uint8_t lastOnLed=0xff;
static uint8_t level_a;
static uint8_t level_b;
static uint8_t level_c;
static uint8_t level_d;


static void RunCmd(void);
static void SideLed_OnOff(uint8_t ledNum,uint8_t onoff);
static void TurnOffAll_Led(void);
static void AdjustBrigtness_Led(uint8_t bightVal);
//static void Order_SideLed(uint8_t orderLed);
static void Spot_SideLed(void);
static void Linear_SideLed(uint8_t ledNum);
static void  BrightnessWhichOne_Linear(uint8_t bightnessVal);
static void  BrightnessWhichOne_Spot(uint8_t bightnessVal);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/*************************************************************************************
**
  * Function Name: void DecodeTestCase(void)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void DecodeTestCase(void)
{
    if(decodeFlag){
        decodeFlag = 0;
        RunCmd();
    }
}
/*************************************************************************************
**
  * Function Name: void RunCmd(void);
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void RunCmd(void)
{
    
    uint8_t cmdType = inputCmd[0]; //order 

    switch(cmdType){

        case 'O' : //0x4F -> "SPOT"board
            classID[0]= 1; //be save sport flag right board
            
            //claseID[2]=ledab.led_LR_id;
            ledab.RunMode = 0;
            Spot_SideLed();
        break;
        
        case 'S'://hex:0X56->liner LED
             classID[0]=2;  //Left board
             classID[1]=ledab.led_LR_id;
             classID[2]= (inputCmd[2]-0x30)*10+inputCmd[3]-0x30;
             ledab.RunMode = 0;
            SideLed_OnOff(((inputCmd[2]-0x30)*10+inputCmd[3]-0x30),1);
        break;

        case 'C': //0X43
            TurnOffAll_Led();
         break;

        case 'A'://0X41
            AdjustBrigtness_Led(inputCmd[1]);
        break;
        default:
        break;


    }
}
/*************************************************************************************
**
  * Function Name: void RunCmd(void);
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
static void SideLed_OnOff(uint8_t ledNum,uint8_t onoff)
{
    if((lastOnLed !=ledNum)||(onoff==0)){
         TurnOffAll_Led();
    }

    if(onoff){

        lastOnLed = ledNum;
           setLevel_A(level_a);
    
           if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) ==0) && (classID[1]==1)){ 
                ledab.RunMode=0;
                hasLedOn_linear =1;
               	//Order_SideLed(ledNum);
                Linear_SideLed(ledNum);
            }
         if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) ==1 && classID[1]==2){ //right side led
                     ledab.RunMode=0;
                      hasLedOn_linear =1;
                   // Order_SideLed(ledNum);
                     Linear_SideLed(ledNum);

           }
           if(classID[1]==3){ //both side led  ON
                ledab.RunMode=0;
                 hasLedOn_linear =1;
               // Order_SideLed(ledNum);
                Linear_SideLed(ledNum);
            }

       
    }
}
/*************************************************************************************
**
  * Function Name: void Order_SideLed(void)
  * Function: Turn on or off side board left or right led 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void Order_SideLed(uint8_t orderLed)
{
       switch(orderLed){

          case 1: //PA6 LINEAR BOARD "IR1-IR730"
			    ledab.runstep =0x11;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
                TurnOff_TheFirstLedA();
				HAL_Delay(20);
				//1.turn on LEDA1 =1
			    HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
			
			//    ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
			//     MX_TIM2_Init();
            //     HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;  //the first group 
			    setLevel_A( level_a);
                
                break;

            case 2: //PA5 LINEAR "IR1-IR850"
			     ledab.runstep =0x12;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
				//   MX_TIM2_Init();
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;

            case 3://PA4 LINEAR "IR3-IR940"
			     ledab.runstep =0x13;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
				//   MX_TIM2_Init();
				// //2. enable
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;

            case 4://PA3 LINEAR "White"
				ledab.runstep =0x14;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6];
				//   MX_TIM2_Init();
			    // //2 .EN
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;

                //the second group led follow down "SPORT BOARD"
                case 5://RGBW-G //SPOT LED
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    HAL_Delay(20);
                    // ledab.pwmDutyCycle_ch2 = aRxBuffer[6];
                    //   MX_TIM2_Init();
                    // HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //TIM2_CH1 the second group
                    //PA15-22PIN--the second group pwm ----Green
                    setLevel_B(level_b);
                break;

                //the third group led 
                case 6://RGBW-B //SPOT //the third group only Pwm control  //PB3 --TIM1-CH2 -AF1
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    HAL_Delay(20);
                    // ledab.pwmDutyCycle_ch3 = aRxBuffer[6];
                    // MX_TIM1_Init();
                    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2 PB3 the third group
                    //PB3-23PIN --the third gropu pwm ---Blue
                    setLevel_C(level_c);
                break;

                //the fourth group led 

                case 7: //PB8 //SPOT  //UV310
                    ledab.runstep =0x41;
                    HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
            
                    HAL_Delay(20);
                    //1.UV_1 LED by control 
                    if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==1){//read LEDD2_EN 

                        ledab.runstep =0x4A;
                        HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                        HAL_GPIO_WritePin(GPIOA, LEDD1_Pin , GPIO_PIN_SET); //
                        HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ;
                    }
                    else if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==0){
                        ledab.runstep =0x4B;
                        HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2); 
                        HAL_GPIO_WritePin(LEDD1_GPIO_Port, LEDD1_Pin, GPIO_PIN_RESET); //Low -works
                        
                        // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                        // MX_TIM3_Init();
                        // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                        setLevel_D( level_d);
                        HAL_UART_Transmit(&huart1,&aRxBuffer[5],1, 2);
                    }
                    ledab.RunMode = 0x41;
                break;

                case 8: //PA11-//SPOT //UV_2 LED-UV275
                    ledab.runstep =0x42;
                    HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
                
                    HAL_Delay(20);

                    //UV_2 led by control 
                    if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==1){
                            HAL_GPIO_WritePin(GPIOA, LEDD2_Pin , GPIO_PIN_SET); //
                            HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ;
                    }
                    else{
                        HAL_GPIO_WritePin(LEDD2_GPIO_Port, LEDD2_Pin, GPIO_PIN_RESET);
                        
                        // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                        // MX_TIM3_Init();
                        // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                        setLevel_D(level_d);
                    //HAL_Delay(100);
                    }
                    ledab.RunMode = 0x42;
                break;
			
                case 9: //PC6 -SPOT -RGBW-W
                    ledab.runstep =0x43;
                    HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
            
                    HAL_Delay(20);

                    //turn on LEDB1
                    HAL_GPIO_WritePin(LEDD3_GPIO_Port, LEDD3_Pin, GPIO_PIN_SET);
                    //  ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                    //  MX_TIM3_Init();
                    //  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                    setLevel_D(level_d);
                break;
			  
			    case 10: //PA8 SPOT --RGBW-R
                    ledab.runstep =0x44;
                    HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                    TurnOff_TheFourthLedD();
                    TurnOff_TheFirstLedA();
                    TurnOff_TheSecondLedB();
                    TurnOff_TheThirdLedC();
                
                    HAL_Delay(20);
                    //turn on LEDB1
                    HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_SET);
                    // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                    // MX_TIM3_Init();
                    // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                    setLevel_D(level_d);
			  
                 break;
                
         }

}
/*************************************************************************************
**
  * Function Name:void Spot_SideLed(void)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
static void Spot_SideLed(void)
{
            hasLedOn_spot =1;
             setLevel();
            //the second group led follow down "SPORT BOARD"
               // case 5://RGBW-G //SPOT LED
                    TurnOff_TheFirstLedA();
                    HAL_Delay(20);
                    // ledab.pwmDutyCycle_ch2 = aRxBuffer[6];
                    //   MX_TIM2_Init();
                    // HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //TIM2_CH1 the second group
                    //PA15-22PIN--the second group pwm ----Green
                    setLevel_B(level_b);
              

                //the third group led 
              //  case 6://RGBW-B //SPOT //the third group only Pwm control  //PB3 --TIM1-CH2 -AF1
            
                    // ledab.pwmDutyCycle_ch3 = aRxBuffer[6];
                    // MX_TIM1_Init();
                    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2 PB3 the third group
                    //PB3-23PIN --the third gropu pwm ---Blue
                    setLevel_C(level_b);
              

                //the fourth group led 

             //   case 7: //PB8 //SPOT  //UV310
                    // ledab.runstep =0x41;
                    // HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
            
                    HAL_Delay(20);
                    //1.UV_1 LED by control 
                    if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==1){//read LEDD2_EN 

                        ledab.runstep =0x4A;
                        HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                        HAL_GPIO_WritePin(GPIOA, LEDD1_Pin , GPIO_PIN_SET); //
                        HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ;
                    }
                    else if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==0){
                        ledab.runstep =0x4B;
                        HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2); 
                        HAL_GPIO_WritePin(LEDD1_GPIO_Port, LEDD1_Pin, GPIO_PIN_RESET); //Low -works
                        
                        // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                        // MX_TIM3_Init();
                        // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                        setLevel_D( level_b);
                        HAL_UART_Transmit(&huart1,&aRxBuffer[5],1, 2);
                    }
                    ledab.RunMode = 0x41;
             //   break;

              //  case 8: //PA11-//SPOT //UV_2 LED-UV275
                    // ledab.runstep =0x42;
                    // HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                
                
                    HAL_Delay(20);

                    //UV_2 led by control 
                    if(HAL_GPIO_ReadPin(LEDD2_EN_GPIO_PORT,LEDD2_EN_Pin)==1){
                            HAL_GPIO_WritePin(GPIOA, LEDD2_Pin , GPIO_PIN_SET); //
                            HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1) ;
                    }
                    else{
                        HAL_GPIO_WritePin(LEDD2_GPIO_Port, LEDD2_Pin, GPIO_PIN_RESET);
                        
                        // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                        // MX_TIM3_Init();
                        // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                        setLevel_D(level_b);
                    //HAL_Delay(100);
                    }
                    ledab.RunMode = 0x42;
             //   break;
			
              //  case 9: //PC6 -SPOT -RGBW-W
                    // ledab.runstep =0x43;
                    // HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
              
            
                    HAL_Delay(20);

                    //turn on LEDB1
                    HAL_GPIO_WritePin(LEDD3_GPIO_Port, LEDD3_Pin, GPIO_PIN_SET);
                    //  ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                    //  MX_TIM3_Init();
                    //  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                    setLevel_D(level_b);
             //   break;
			  
			  //  case 10: //PA8 SPOT --RGBW-R
                    // ledab.runstep =0x44;
                    // HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
                   
                    HAL_Delay(20);
                    //turn on LEDB1
                    HAL_GPIO_WritePin(LEDD4_GPIO_Port, LEDD4_Pin, GPIO_PIN_SET);
                    // ledab.pwmDutyCycle_ch4 = aRxBuffer[6];
                    // MX_TIM3_Init();
                    // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ;
                    setLevel_D(level_b);
			     // break;
                



}
/*************************************************************************************
**
  * Function Name:void Linear_SideLed(void)
  * Function: Open linear board LED 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
static void Linear_SideLed(uint8_t ledNum)
{
        switch(ledNum){

          
          case 0: //PA6 LINEAR BOARD "IR1-IR730"
			    ledab.runstep =0x11;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
                TurnOff_TheFirstLedA();
				HAL_Delay(20);
				//1.turn on LEDA1 =1
			    HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
			
			//    ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
			//     MX_TIM2_Init();
            //     HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;  //the first group 
			    setLevel_A( level_a);
                
                break;

            case 1: //PA5 LINEAR "IR1-IR850"
			     ledab.runstep =0x12;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
				//   MX_TIM2_Init();
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;

            case 2://PA4 LINEAR "IR3-IR940"
			     ledab.runstep =0x13;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6] ;
				//   MX_TIM2_Init();
				// //2. enable
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;

            case 3://PA3 LINEAR "White"
				ledab.runstep =0x14;
				HAL_UART_Transmit(&huart1,&ledab.runstep,1, 2);
				TurnOff_TheSecondLedB();
			    TurnOff_TheThirdLedC();
			    TurnOff_TheFourthLedD();
				TurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
				//  ledab.pwmDutyCycle_ch1 = aRxBuffer[6];
				//   MX_TIM2_Init();
			    // //2 .EN
				//  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;
				 setLevel_A(level_a);
                break;
                default:

                break;
        }  

}


void setLevel(void)
{
    // setLevel_B(level_a);
     setLevel_B(level_b);
     setLevel_C(level_b);
     setLevel_D(level_b);

}
/*************************************************************************************
**
  * Function Name: void setLevel_A(level)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void setLevel_A(uint8_t level)
{
    if(level<LEVEL_MIN) level=LEVEL_MIN;
   
    ledab.pwmDutyCycle_ch1 =level;// level * LEVEL_PWM_STEP;
   // if(ledab.pwmDutyCycle_ch1 > LEVEL_PWM_MAX) ledab.pwmDutyCycle_ch1=LEVEL_PWM_MAX;
    MX_TIM2_Init();
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) ;  //the first group 
}

void setLevel_B(uint8_t level)
{
	if(level<LEVEL_MIN) level=LEVEL_MIN;
    ledab.pwmDutyCycle_ch2 = level;//level * LEVEL_PWM_STEP;
   // if(ledab.pwmDutyCycle_ch2> LEVEL_PWM_MAX) ledab.pwmDutyCycle_ch2=LEVEL_PWM_MAX;
	 MX_TIM2_Init();
	 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //TIM2_CH1 the second group
}

void setLevel_C(uint8_t level)
{
	if(level<LEVEL_MIN) level=LEVEL_MIN;
    ledab.pwmDutyCycle_ch3 = level;//level * LEVEL_PWM_STEP;
    //if(ledab.pwmDutyCycle_ch3> LEVEL_PWM_MAX) ledab.pwmDutyCycle_ch3=LEVEL_PWM_MAX;
	MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2 PB3 the third group

}

void setLevel_D(uint8_t level)
{
	if(level<LEVEL_MIN) level=LEVEL_MIN;
    ledab.pwmDutyCycle_ch4 = level;//level * LEVEL_PWM_STEP;
   // if(ledab.pwmDutyCycle_ch4> LEVEL_PWM_MAX) ledab.pwmDutyCycle_ch4=LEVEL_PWM_MAX;
	MX_TIM3_Init();
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) ; //TIM3_CH1 the fourth group

}
/*************************************************************************************
**
  * Function Name: AdjustBrigtness_Led(uint8_t ledNum)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void AdjustBrigtness_Led(uint8_t bightVal)
{
    uint8_t cmdType = classID[0]; //order 

    if(hasLedOn_linear == 1 || hasLedOn_spot==1)
	{
		switch(cmdType){
            case 1 : //0x4F -> "SPOT"board
                    BrightnessWhichOne_Spot(bightVal);
                    Spot_SideLed();
            break;

            case 2:
                if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) ==0) && (classID[1]==1)){ 
                
                     BrightnessWhichOne_Linear(bightVal);
                     Linear_SideLed(classID[2]);
                }
                if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) ==1 && classID[1]==2){ //right side led
                    BrightnessWhichOne_Linear(bightVal);
                    Linear_SideLed(classID[2]);

                }
                if(classID[1]==3){ //both side led  ON
                    BrightnessWhichOne_Linear(bightVal);
                    Linear_SideLed(classID[2]);
                }
            break;
            default :
            break;
        }
    }

}
/*************************************************************************************
**
  * Function Name: AdjustBrigtness_Led(uint8_t ledNum)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void BrightnessWhichOne_Spot(uint8_t val)
{
    
      if(val=='1')	// adj +
		{
				level_b+=LEVEL_STEP;
				if(level_b>LEVEL_PWM_MAX ) level_b=LEVEL_PWM_MAX ;
		}
		else	// adj -
        {
            if(level_b<LEVEL_MIN)	level_b=LEVEL_MIN;
            else 	level_b-=LEVEL_STEP;
        }
       
        setLevel_B(level_b);
        setLevel_C(level_b);
        setLevel_D(level_b);

}
/*************************************************************************************
**
  * Function Name: void BrightnessWhichOne_Linear(uint8_t val)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void BrightnessWhichOne_Linear(uint8_t val)
{
    
      if(val=='1')	// adj +
		{
				level_a+=LEVEL_STEP;
				if(level_a>LEVEL_PWM_MAX ) level_a=LEVEL_PWM_MAX ;
		}
		else	// adj -
        {
            if(level_a<LEVEL_MIN)	level_a=LEVEL_MIN;
            else 	level_a-=LEVEL_STEP;
        }
       
        setLevel_A(level_a);
       

}
/*************************************************************************************
**
  * Function Name: AdjustBrigtness_Led(uint8_t ledNum)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void TurnOffAll_Led(void)
{
    	
    TurnOff_TheSecondLedB();
    TurnOff_TheThirdLedC();
    TurnOff_TheFourthLedD();
    TurnOff_TheFirstLedA();
}
/*************************************************************************************
**
  * Function Name: void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
  * Function: 
  * Input Ref: NO
  * Return Ref:NO
*
**************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	switch(state)
	{
	case STATE_PREAMBLE1:
		if(aRxBuffer[0]=='V' || aRxBuffer[0] =='Z') // hex:56
			state=STATE_PREAMBLE2;
		break;
	case STATE_PREAMBLE2:
		if(aRxBuffer[0]=='X') // hex:58
		{
			state=STATE_ADDR;
		}
		else
			state=STATE_PREAMBLE1;  
		break;
	case STATE_ADDR:
		if(aRxBuffer[0]==BOARD_ADDR) //"L" -0x4C
		{
			state=STATE_CMD; 
		}
		else
			state=STATE_PREAMBLE1; 
		break;
	case STATE_CMD:
		inputCmd[0]=aRxBuffer[0]; //hex:53-->'S'->linear led  'A'-0X41->Brightness 
         // 'O'-0X4F->SOPT ,'C'-0X43->Close LED 
		crcCheck = 0x55 ^ inputCmd[0];
		//decodeFlag=1;
		state=STATE_SIZE; //Next receive has parameter
		break;
	case STATE_SIZE:
		cmdSize=aRxBuffer[0]-0x30;  //parameter of number 
		if(cmdSize>MAX_CMD_PARA_SIZE)	// out of range
		{
			state=STATE_PREAMBLE1;
		}
		else if(cmdSize>0 )
		{
			paraIndex=1;
            crcCheck ^= aRxBuffer[0];
            state=STATE_PARA;
            
		}
		else	// no parameter
		{
			crcCheck ^= aRxBuffer[0];
			decodeFlag=1;
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_PARA:
		inputCmd[paraIndex]=aRxBuffer[0];//inputCmd[1]
		crcCheck ^= aRxBuffer[0];
		paraIndex++;  
		cmdSize--;
		if(cmdSize==0)
		{
			if(inputCmd[0] != 'A')
                ledab.led_LR_id=inputCmd[1] - 0x30;
            HAL_UART_Transmit(&huart1,&inputCmd[1],1,2);
			HAL_UART_Transmit(&huart1,&inputCmd[2],1,2);
            HAL_UART_Transmit(&huart1,&inputCmd[3],1,2);
			decodeFlag=1; //receive UART data
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_CRC:
		//if((crcCheck ^ aRxBuffer[0])==0)
		{
			//decodeFlag=1;
		}
		state=STATE_PREAMBLE1;
		break;
	default:
		state=STATE_PREAMBLE1;
		decodeFlag=0;
	}
	HAL_UART_Receive_IT(&huart1,aRxBuffer,1);

}
