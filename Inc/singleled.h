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

void RedLed(void);
void GreenLed(void);
void BlueLed(void);

void RedGreenBlue_LED_Com(void);



typedef struct _ledabled_
{
  uint8_t led_red;
  uint8_t led_green;
  uint8_t led_blue;
  uint8_t led_one;
  uint8_t led_four;
  uint8_t led_by_cd;
  uint8_t runstep;
  uint8_t left_side;
  uint8_t led_LR_id;
  uint8_t pwmDutyCycle_ch1;
  uint8_t pwmDutyCycle_ch2;
  uint8_t pwmDutyCycle_ch3;
  uint8_t pwmDutyCycle_ch4;
    
}led;

extern led ledab;

#endif
