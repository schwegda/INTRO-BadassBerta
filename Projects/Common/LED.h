/*
 * LED.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */

#ifndef LED_H_
#define LED_H_

#if PL_NOF_LEDS >= 1
  #include "LED_RGB_R.h"
  #define LED1_On()     LedBit1_ClrVal()
  #define LED1_Off()    LedBit1_SetVal()
  #define LED1_Neg()    LedBit1_NegVal()
  #define LED1_Get()    LedBit1_GetVal()
  #define LED1_Put(val) LedBit1_PutVal(!val)
  #define LED1_Init()   /* do nothing */
  #define LED1_Deinit() /* do nothing */
#else
  #define LED1_On()     /* do nothing */
  #define LED1_Off()    /* do nothing */
  #define LED1_Neg()    /* do nothing */
  #define LED1_Get()  0 /* do nothing */
  #define LED1_Put(val) /* do nothing */
  #define LED1_Init()   /* do nothing */
  #define LED1_Deinit() /* do nothing */
#endif

#if PL_NOF_LEDS >= 2
  #include "LedBit2.h"
  #define LED2_On()     LedBit2_ClrVal()
  #define LED2_Off()    LedBit2_SetVal()
  #define LED2_Neg()    LedBit2_NegVal()
  #define LED2_Get()    LedBit2_GetVal()
  #define LED2_Put(val) LedBit2_PutVal(!val)
  #define LED2_Init()   /* do nothing */
  #define LED2_Deinit() /* do nothing */
#else
  #define LED2_On()     /* do nothing */
  #define LED2_Off()    /* do nothing */
  #define LED2_Neg()    /* do nothing */
  #define LED2_Get()  0 /* do nothing */
  #define LED2_Put(val) /* do nothing */
  #define LED2_Init()   /* do nothing */
  #define LED2_Deinit() /* do nothing */
#endif



void LED_Init(void);
void LED_Deinit(void);

#endif /* LED_H_ */
