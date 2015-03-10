/*
 * Platform.c
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */

/* ###################################################################
**     Filename    : Platform.c
**     Project     : INTRO
**     Processor   : MK22FX512VLQ12 / MKL25Z128VLK4
**     Version     : Driver 01.0
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-1, 08:21, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**     Contents    :
**
**
** ###################################################################*/
/*!
** @file Platform.c
** @version 01.00
** @brief
**
** @detail
**
*/
/*!
**  @addtogroup Platform_module Platform Module documantation
**  @{
*/

#include "Platform.h"
#include "LED.h"
#include "Event.h"

void PL_Init(void)
{
#if PL_HAS_LED
	LED_Init();
#endif
#if PL_HAS_EVENTS
	EVNT_Init();
#endif
}

void PL_Deinit(void)
{
#if PL_HAS_LED
	LED_Deinit();
#endif
#if PL_HAS_EVENTS
	EVNT_Deinit();
#endif
}


/*!
** @}
*/

