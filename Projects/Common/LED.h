/*
 * LED.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */

#ifndef LED_H_
#define LED_H_
#include "Platform.h"

/* On FRDM Board :
 * 		- LED1 -> RGB Red
 * 		- LED2 -> RGB Blue
 * 		- LED3 -> RGB Green
 */

#if PL_NOF_LEDS >= 1
  #include "LED_1.h"
  #define LED1_On()     LED_1_On()
  #define LED1_Off()    LED_1_Off()
  #define LED1_Neg()    LED_1_Neg()
  #define LED1_Get()    LED_1_Get()
  #define LED1_Put(val) LED_1_Put(!val)
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
  #define LED2_On()     LED_2_On()
  #define LED2_Off()    LED_2_Off()
  #define LED2_Neg()    LED_2_Neg()
  #define LED2_Get()    LED_2_Get()
  #define LED2_Put(val) LED_2_Put(!val)
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
  #define LED3_On()     LED_3_On()
  #define LED3_Off()    LED_3_Off()
  #define LED3_Neg()    LED_3_Neg()
  #define LED3_Get()    LED_3_Get()
  #define LED3_Put(val) LED_3_Put(!val)
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
