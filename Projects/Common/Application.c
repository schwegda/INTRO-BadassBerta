/*
 * Application.c
 *
 *  Created on: 10.03.2015
 *      Author: David Schwegler
 */

/*!
** @file Application.c
** @version 01.00
** @brief
**  	Application main routine implementation.
**      This module is our main loop program so you don't have to modify main.c.
**      This module manage all events.
** @detail
**
*/


#include "PE_Types.h"
#include "Platform.h"
#include "LED.h"
#include "Application.h"
#include "WAIT1.h"
#include "Event.h"


static void APP_HandleEvents(EVNT_Handle event)
{
	switch(event){
	case EVENT_STARTUP:
		LED1_On();
		WAIT1_Waitms(50);
		LED1_Off();
		break;
	default:
		break;
	}
}

static void APP_Task(void)
{
	EVNT_SetEvent(EVENT_STARTUP);	/* set startup event */
	for(;;){
		EVNT_HandleEvent(APP_HandleEvents);
		WAIT1_Waitms(100); /* wait some time */
	}
}

void initApplication()
{
	PL_Init();
	APP_Task();
}

void runApplication()
{
#if 0
	for(;;)
		{
			LED1_On();
			WAIT1_Waitms(500);
			LED1_Off();
			LED2_On();
			WAIT1_Waitms(500);
			LED2_Off();
			LED3_On();
			WAIT1_Waitms(500);
			LED3_Off();
		}
#endif
}

void deinitApplication()
{
	PL_Deinit();
	/*! do nothing*/
}

