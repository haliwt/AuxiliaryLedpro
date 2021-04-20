#include "singleled.h"
#include "gpio.h"

static void TheFirstGroup_SingleLEDA(uint8_t ledvala);
static void TheSecondGroup_SingleLEDB(uint8_t ledvalb);

void SingleLed_Test(void)
{

    uint8_t cmdType_0 = aRxBuffer[0]; //command order 0
    uint8_t cmdType_1 = aRxBuffer[1]; //command order 1
    uint8_t cmdType_3 = aRxBuffer[2]; //check sum codes
    if(cmdType_3 == 0xAA){
        
        TheFirstGroup_SingleLEDA(cmdType_0);
        TheSecondGroup_SingleLEDB(cmdType_1);
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
static void TheFirstGroup_SingleLEDA(uint8_t ledvala)
    {
        //uint8_t cmdType_2 = aRxBuffer[2]; //the first group   LEDAxx LED

        if (ledvala > 7)
        {
          HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin | LEDA2_Pin | LEDA3_Pin | LEDA4_Pin | LEDA5_Pin | LEDA6_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin | LEDA8_Pin, GPIO_PIN_RESET);
        }
        else
        {
            switch (ledvala)
            {

            case 0:
							  //1. Disable EN 
									HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
						      HAL_GPIO_WritePin(LEDACUT_GPIO_Port, LEDACUT_Pin, GPIO_PIN_RESET);
						    //2. turn off LEDA8
						     HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
						     //1.turn on LEDA1 =1
						    HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
						    //2.EN on
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                
                break;

            case 1:
							  //1.Disable EN 
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
						    //2. turn off LEDA1
                HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 2:
							  //1.Diable EN
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
						    //turn off LEDA2
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
						    //2. enable
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 3:
							   //1.Disable EN
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
                //turn off LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_RESET);
						    HAL_Delay(500);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 4:
							  //1.Disable EN 
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
                //turn off LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA5
                HAL_GPIO_WritePin(LEDA5_GPIO_Port, LEDA5_Pin, GPIO_PIN_SET);      //1.the first turn on LED
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 5:
							  //1.disable 
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
                //turn off LEDA5
                HAL_GPIO_WritePin(LEDA5_GPIO_Port, LEDA5_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA6
                HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 6:
							  //1.disable en
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
                //turn off LEDA6
                HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 7:
							   //1.disable en
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
                //turn off LEDA7
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
                //turn on LEDA8
                HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
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
static void TheSecondGroup_SingleLEDB(uint8_t ledvalb)
{
       // uint8_t cmdType_3 = aRxBuffer[3]; //the first group   LEDAxx LED

       if (ledvalb > 7)
       {
           HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin | LEDB2_Pin | LEDB3_Pin, GPIO_PIN_RESET);
           HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin | LEDB5_Pin | LEDB7_Pin, GPIO_PIN_RESET);
           HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
        }
        else
        {
            switch (ledvalb)
            {

            case 0:
							 //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB8 = 0
						    HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
						   //1.turn on LEDB1 =1
                HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 1:
							   //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB1 = 0
						    HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
						   //turn on LEDB1
                HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 2:
							   //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB2 = 0
						    HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
							  //turn on LEDB3=1
                HAL_GPIO_WritePin(LEDB3_GPIO_Port, LEDB3_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 3:
							  //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB3 = 0
						    HAL_GPIO_WritePin(LEDB3_GPIO_Port, LEDB3_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
							  //turn on LEDB4=1
                HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 4:
							  //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB4 = 0
						    HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
							  //turn on LEDB5=1
                HAL_GPIO_WritePin(LEDB5_GPIO_Port, LEDB5_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 5:
                // HAL_GPIO_WritePin(LEDB6_GPIO_Port,LEDB6_Pin, GPIO_PIN_SET);
                break;

            case 6:
							 //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB5 = 0
						    HAL_GPIO_WritePin(LEDB5_GPIO_Port, LEDB5_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
							  //turn on LEDB7 =1
                HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 7:
								 //1.disable en
							  HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
						   //2. turn off LEDB7 = 0
						    HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_RESET);
								HAL_Delay(500);
						    //turn on LEDB8 =1
                HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;
            }
        }
 }


