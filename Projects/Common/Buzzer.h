/*
 * Buzzer.h
 *
 *  Created on: 16.03.2015
 *      Author: Alexander
 */
/*!
**  @addtogroup Buzzer_module Buzzer module documentation
**  @{
*/
/* MODULE Buzzer */
#ifndef BUZZER_H_
#define BUZZER_H_
#include "Platform.h"

#if PL_HAS_BUZZER >= 1
  #include "Buzzer_PE.h"
  #define Buzzer_On() Buzzer_PE_SetVal()
  #define Buzzer_Off() Buzzer_PE_ClrVal()
  #define Buzzer_GetValue() Buzzer_PE_GetVal()
  #define Buzzer_Negate() Buzzer_PE_NegVal()

#else
  #define Buzzer_On() 		/* do nothing */
  #define Buzzer_Off() 		/* do nothing */
  #define Buzzer_GetValue() /* do nothing */
  #define Buzzer_Negate() 	/* do nothing */
#endif

#endif /* BUZZER_H_ */
/*@}
 */
