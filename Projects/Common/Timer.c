/**
 * \file Timer.h
 * \brief Timer driver interface implementation.
 * \author David Schwegler
 *
 * This module implements the driver for the timers used in the system.
 */


#include "Timer.h"
#include "Event.h"
#include "Trigger.h"
#if PL_HAS_PID
	#include "Pid.h"
	#include "Motor.h"
#endif
#if PL_HAS_MOTOR_TACHO
	#include "Tacho.h"
#endif

void TMR_OnInterrupt(void)
{
	/* this method gets called from FRROS1 Tick Hock interrupt */
	static int cntr=0;
	cntr++;

	if(cntr==(1000/TMR_TICK_MS))
	{
		EVNT_SetEvent(EVNT_LED_HEARTBEAT);
		cntr = 0;
	}

#if PL_HAS_TRIGGER
	TRG_IncTick();
#endif

#if PL_HAS_MOTOR_TACHO
	TACHO_Sample();
#endif

}

void TMR_Init(void)
{
	/* nothing needed right now */
}


void TMR_Deinit(void)
{
	/* nothing needed right now */
}
