/*
 * Buzzer.h
 *
 *  Created on: 16.03.2015
 *      Author: Alexander
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "Platform.h"

#if PL_HAS_BUZZER >= 1
  #include "Buzzer_PE.h"
  #define Buzzer_PE_SetVal() Buzzer_On()
  #define Buzzer_PE_GetVal() Buzzer_GetValue()
  #define Buzzer_PE_ClrVal() Buzzer_Off()
  #define Buzzer_Init()

#else
//  #define LED1_On()     /* do nothing */
#endif





#endif /* BUZZER_H_ */
