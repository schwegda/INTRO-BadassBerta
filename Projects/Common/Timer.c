/**
 * \file Timer.h
 * \brief Timer driver interface implementation.
 * \author David Schwegler
 *
 * This module implements the driver for the timers used in the system.
 */


#include "Timer.h"
#include "Event.h"

void TMR_OnInterrupt(void)
{
	/* this method gets called from TimerInt(TI1) */
	static int cntr=0;
	cntr++;

	if(cntr==(1000/TMR_TICK_MS))
	{
		EVNT_SetEvent(EVENT_LED_HEARTBEAT);
		cntr = 0;
	}
}

void TMR_Init(void)
{
	/* nothing needed right now */
}


void TMR_Deinit(void)
{
	/* nothing needed right now */
}
