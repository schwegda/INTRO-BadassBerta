/*
 * LED.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */

#ifndef LED_H_
#define LED_H_
#include "Platform.h"

#if PL_NOF_LEDS >= 1
  #include "LED_1.h"
  #define LED1_On()     LED_1_On()
  #define LED1_Off()    LED_1_Off()
  #define LED1_Neg()    LED_1_Neg()
  #define LED1_Get()    LED_1_GetVal()
  #define LED1_Put(val) LED_1_PutVal(!val)
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
  #include "LED_2.h"
  #define LED2_On()     LED_2_ClrVal()
  #define LED2_Off()    LED_2_SetVal()
  #define LED2_Neg()    LED_2_NegVal()
  #define LED2_Get()    LED_2_GetVal()
  #define LED2_Put(val) LED_2_PutVal(!val)
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

#if PL_NOF_LEDS >= 3
  #include "LED_3.h"
  #define LED3_On()     LED_3_ClrVal()
  #define LED3_Off()    LED_3_SetVal()
  #define LED3_Neg()    LED_3_NegVal()
  #define LED3_Get()    LED_3_GetVal()
  #define LED3_Put(val) LED_3_PutVal(!val)
  #define LED3_Init()   /* do nothing */
  #define LED3_Deinit() /* do nothing */
#else
  #define LED3_On()     /* do nothing */
  #define LED3_Off()    /* do nothing */
  #define LED3_Neg()    /* do nothing */
  #define LED3_Get()  0 /* do nothing */
  #define LED3_Put(val) /* do nothing */
  #define LED3_Init()   /* do nothing */
  #define LED3_Deinit() /* do nothing */
#endif

void LED_Init(void);
void LED_Deinit(void);

#endif /* LED_H_ */
