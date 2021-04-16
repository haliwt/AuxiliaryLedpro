#include "txdecode.h"
#include "gpio.h"
#include "singleled.h"
#include "usart.h"

led ledab;
uint8_t txdata;
uint8_t led_by_id;  //A? ?? B ?
uint8_t led_by_A;   //A
uint8_t led_by_B;  //

static uint8_t BCC(void);




void TxDecode(void)
{
    uint8_t cmdType_0 =  aRxBuffer[0] ; //command order 0
	uint8_t cmdType_1 =  aRxBuffer[1] ; //command order 1
	uint8_t cmdType_2 =  aRxBuffer[2] ;  //group A led
	uint8_t cmdType_3 =  aRxBuffer[3];   //group B led
	uint8_t cmdType_4 =  aRxBuffer[4];		   //group B led
	uint8_t cmdType_5 =  aRxBuffer[5];				   //group B led
	uint8_t cmdType_6 =  aRxBuffer[6] ; //check sum codes

	uint8_t tembyte = 0xAA ^ cmdType_2 ^ cmdType_3 ^ cmdType_4 ^ cmdType_5;

	switch (cmdType_0)
	{

	case 0x42:

		if (cmdType_1 == 0x4c)
		{
			if (cmdType_6 == tembyte)
			{
				ledab.led_by_a = cmdType_2; //group A led
				ledab.led_by_b = cmdType_3; //group B led
				TheFirstGroup_SingleLEDA();
				TheSecondGroup_SingleLEDB();
			}
		}
		else
		{

			return;
		}

		break;
	default:

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
	*Function Name: void CheckRun(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void CheckRun(void)
{
	switch(led_by_id){

		case 0:

		break;

		case 1 :  //A group
		       
			   TheFirstGroup_SingleLEDA();

		break;

		case 2:   //B group
               TheSecondGroup_SingleLEDB();
		break;

		default:

		break;
	}

}
/*************************************************************************
 	*
	*Function Name: void CheckRun(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/