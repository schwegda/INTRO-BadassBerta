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
#include "Keys.h"
#include "Buzzer.h"
#include "CLS1.h"
/*!
 * \brief Application event handler
 * \param event Event to be handled
 */
static void APP_HandleEvents(EVNT_Handle event)
{
	switch(event){
	case EVNT_STARTUP:
		LED1_On();
		WAIT1_Waitms(50);
		LED1_Off();
		for(int i=0;i<30;i++)
		{
			Buzzer_Negate();
			WAIT1_Waitms(5);
		}
		break;
	case EVNT_LED_HEARTBEAT:
		LED1_Neg();
		break;

		#if PL_NOF_KEYS >= 1
			case EVNT_SW1_PRESSED:
				LED1_Neg();
				Buzzer_Negate();

                CLS1_SendStr("CollStuff \n", CLS1_GetStdio()->stdOut);

			  break;
		#endif

		#if PL_NOF_KEYS >= 2
			case EVNT_SW2_PRESSED:
				LED2_Neg();
			  //CLS1_SendStr("SW2\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 3
			case EVNT_SW3_PRESSED:
				LED3_Neg();
			  //CLS1_SendStr("SW3\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 4
			case EVNT_SW4_PRESSED:
			  //CLS1_SendStr("SW4\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 5
			case EVNT_SW5_PRESSED:
			  //CLS1_SendStr("SW5\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 6
			case EVNT_SW6_PRESSED:
			  //CLS1_SendStr("SW6\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 7
			case EVNT_SW7_PRESSED:
			  //CLS1_SendStr("SW7\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		default:
		break;
	}
}

/*!
 * \brief Application main 'task'.
 */
static void APP_Task(void)
{
	EVNT_SetEvent(EVNT_STARTUP);	/* set startup event */
	for(;;){
		EVNT_HandleEvent(APP_HandleEvents);
		WAIT1_Waitms(100); /* wait some time */
	}
}

void initApplication()
{
	PL_Init();
	CLS1_SendStr("Hello I'am BadassBerta and I'm going to destroy you!\n",CLS1_GetStdio()->stdOut);
	CLS1_SendNum32s(23452345,CLS1_GetStdio()->stdOut);
}

void runApplication()
{
	APP_Task(); 	/* never runs further */

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

