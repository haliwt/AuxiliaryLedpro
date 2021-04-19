#include "txdecode.h"
#include "gpio.h"




static uint8_t BCC(void);
static void TheFirstGroupLEDA(void);
static void TheSecondGroupLEDB(void);



void TxDecode(void)
{
  uint8_t cmdType_0 =aRxBuffer[0] ; //command order 0
	uint8_t cmdType_1 =aRxBuffer[1] ; //command order 1
	uint8_t cmdType_6 =aRxBuffer[6] ; //check sum codes   
	  
	 switch(cmdType_0){
		
		  case 0x42:
				
			    if(cmdType_1 == 0x4c){
						 if(cmdType_6 ==BCC()){
						 	   TheFirstGroupLEDA();
							   TheSecondGroupLEDB();
							}
					
					}
					else{
					
					  return ;
					}
				
			
			break;
		
		
		
		}

}

/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
static uint8_t BCC(void)
{
   uint8_t i;
	 
	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
	
    for (i = 3; i <6; i++) {
        tembyte ^=aRxBuffer[i];
    }
    return tembyte;

}
/*************************************************************************
 	*
	*Function Name: void TheFirstGroupLEDA(void)
	*Function : Turn On LEDAxx LED
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
static void TheFirstGroupLEDA(void)
{
		uint8_t cmdType_2 =aRxBuffer[2] ; //the first group   LEDAxx LED
	
	  if(cmdType_2 > 7)
		{
			 HAL_GPIO_WritePin(LEDA1_GPIO_Port,LEDA1_Pin|LEDA2_Pin|LEDA3_Pin|LEDA4_Pin|LEDA5_Pin|LEDA6_Pin,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(LEDA7_GPIO_Port,LEDA7_Pin|LEDA8_Pin,GPIO_PIN_RESET);
		
		}
		else{
			switch(cmdType_2){
				
				case 0:
					 HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				   HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
					 HAL_GPIO_WritePin(LEDA1_GPIO_Port,LEDA1_Pin, GPIO_PIN_SET);
				break;
				
				case 1: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				    HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA2_GPIO_Port,LEDA2_Pin, GPIO_PIN_SET);
				break;
				
				case 2: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA3_GPIO_Port,LEDA3_Pin, GPIO_PIN_SET);
				break;
				
				case 3: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA4_GPIO_Port,LEDA4_Pin, GPIO_PIN_SET);
				break;
				
				case 4: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA5_GPIO_Port,LEDA5_Pin, GPIO_PIN_SET);
				break;
				
				case 5: 
					   HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA6_GPIO_Port,LEDA6_Pin, GPIO_PIN_SET);
				break;
				
				case 6: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA7_GPIO_Port,LEDA7_Pin, GPIO_PIN_SET);
				break;
				
				case 7: 
					  HAL_GPIO_WritePin(LEDAPWM_GPIO_Port,LEDAPWM_Pin, GPIO_PIN_SET);
				      HAL_GPIO_WritePin(LEDACUT_GPIO_Port ,LEDACUT_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LEDA8_GPIO_Port,LEDA8_Pin, GPIO_PIN_SET);
				break;
			}
	}

}

/*************************************************************************
 	*
	*Function Name: void TheSecondGroupLEDB(void)
	*Function : Turn On LEDBxx LED the second group LED on
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
static void TheSecondGroupLEDB(void)
{
		uint8_t cmdType_3 =aRxBuffer[3] ; //the first group   LEDAxx LED
	
	  if(cmdType_3 > 7){
		   HAL_GPIO_WritePin(LEDB1_GPIO_Port,LEDB1_Pin|LEDB2_Pin|LEDB3_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(LEDB4_GPIO_Port,LEDB4_Pin|LEDB5_Pin|LEDB7_Pin, GPIO_PIN_RESET);
		   HAL_GPIO_WritePin(LEDB8_GPIO_Port,LEDB8_Pin, GPIO_PIN_RESET);
		}
	  else{
	  switch(cmdType_3){
		
			  case 0:
					 HAL_GPIO_WritePin(LEDB1_GPIO_Port,LEDB1_Pin, GPIO_PIN_SET);
				break;
				
				case 1:
					 HAL_GPIO_WritePin(LEDB2_GPIO_Port,LEDB2_Pin, GPIO_PIN_SET);
				break;
				
				case 2:
					 HAL_GPIO_WritePin(LEDB3_GPIO_Port,LEDB3_Pin, GPIO_PIN_SET);
				break;
				
				case 3:
					 HAL_GPIO_WritePin(LEDB4_GPIO_Port,LEDB4_Pin, GPIO_PIN_SET);
				break;
				
				case 4:
					 HAL_GPIO_WritePin(LEDB5_GPIO_Port,LEDB5_Pin, GPIO_PIN_SET);
				break;
				
				case 5:
					// HAL_GPIO_WritePin(LEDB6_GPIO_Port,LEDB6_Pin, GPIO_PIN_SET);
				break;
				
				case 6:
					 HAL_GPIO_WritePin(LEDB7_GPIO_Port,LEDB7_Pin, GPIO_PIN_SET);
				break;
				
				case 7:
					 HAL_GPIO_WritePin(LEDB8_GPIO_Port,LEDB8_Pin, GPIO_PIN_SET);
				break;
		
			}
	  }
}