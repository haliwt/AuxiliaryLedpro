#ifndef __SIDELED_H
#define __SIDELED_H
#include "main.h"
#include "gpio.h"
#include "singleled.h"

#define LEVEL_DEFAULT	  24
#define LEVEL_MAX		   20
#define LEVEL_MIN		   20
#define LEVEL_ZERO		   0
#define LEVEL_STEP		   5
#define LEVEL_PWM_STEP	   1
#define LEVEL_PWM_MAX	    100

#define BUFFER_SIZE     8
extern uint8_t inputCmd[BUFFER_SIZE];

void setLevel(void);

void DecodeTestCase(void);


void setLevel_A(uint8_t vala);
void setLevel_B(uint8_t valb);
void setLevel_C(uint8_t valc);
void setLevel_D(uint8_t vald);


#endif 


