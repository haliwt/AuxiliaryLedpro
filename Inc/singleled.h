#ifndef __SINGLELED_H
#define __SINGLELED_H
#include "main.h"

void SingleLed_Test(void);

void TurnOff_TheSecondLedB(void);
void TurnOff_TheFirstLedA(void);
void TurnOff_TheThirdLedC(void);
void TurnOff_TheFourthLedD(void);

void TheFirstGroup_SingleLEDA(void);  //the first group led
void TheSecondGroup_SingleLEDB(void); //the second group led
void TheThirdGroup_SingleLEDC(void);  //the third group led
void TheFourthGroup_SingleLEDD(void); //the fourth group led

void LR_Control(uint8_t fanval);

typedef struct _ledabled_
{
  uint8_t led_by_a;
  uint8_t led_by_b;
  uint8_t led_by_c;
  uint8_t led_by_d;
    
}led;

extern led ledab;

#endif
