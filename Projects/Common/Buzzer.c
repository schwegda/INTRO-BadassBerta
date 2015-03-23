/*
 * Buzzer.c
 *
 *  Created on: 16.03.2015
 *      Author: Alexander
 */
/*!
**  @addtogroup Buzzer_module Buzzer module documentation
**  @{
*/
/* MODULE Buzzer */
#include "Buzzer.h"
#include "Trigger.h"


void beep(uint16_t ms){
	Buzzer_On();
#if PL_HAS_TRIGGER
	TRG_SetTrigger(TRG_BUZZER_OFF,(ms/TRG_TICKS_MS), beep_Off ,0);
#endif
}

static void beep_Off(){
	Buzzer_Off();
}

/*@}
 */
