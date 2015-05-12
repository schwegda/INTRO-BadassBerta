/*
 * Application.c
 *
 *  Created on: 10.03.2015
 *      Author: David Schwegler
 */

/*!
** @file Application.c
** @version 01.00
** @author David Schwegler, david.schwegler@stud.hslu.ch
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
#include "Trigger.h"
#include "KeyDebounce.h"
#include "RTOS.h"
#include "Shell.h"
#include "ShellQueue.h"
#include "Reflectance.h"
#if configUSE_TRACE_HOOKS
  #include "RTOSTRC1.h"
#endif
#include "Accel.h"
#include "Zumo.h"

/*!
 * \brief Application event handler
 * \param event Event to be handled
 */
static void APP_HandleEvents(EVNT_Handle event)
{
	switch(event){
		case EVNT_STARTUP:
			LED1_On();
			WAIT1_WaitOSms(50);
			LED1_Off();
#if PL_HAS_BUZZER
				BUZ_Beep(300, 500);
#endif
			break;

		case EVNT_LED_HEARTBEAT:
			LED1_Neg();
			break;

		#if PL_NOF_KEYS >= 1
			case EVNT_SW1_PRESSED:
#if PL_IS_ROBO
				if(ZUMO_isBattleDisabled()){
					ZUMO_EnterBattleMode();
				}else{
					ZUMO_LeaveBattleMode();
				}
#endif

				CLS1_SendStr("SW1 pressed \r\n", CLS1_GetStdio()->stdOut);
			  break;

			case EVNT_SW1_LPRESSED:
				CLS1_SendStr("SW1 long pressed \n", CLS1_GetStdio()->stdOut);
#if PL_HAS_LINE_SENSOR
				REF_SetCalinrationFlag(TRUE);
#endif
			break;

		    case EVNT_SW1_RELEASED:
		        CLS1_SendStr("SW1 release\r\n", CLS1_GetStdio()->stdOut);
		    break;
		#endif

		#if PL_NOF_KEYS >= 2
			case EVNT_SW2_PRESSED:
			  CLS1_SendStr("SW2\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 3
			case EVNT_SW3_PRESSED:
			  CLS1_SendStr("SW3\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 4
			case EVNT_SW4_PRESSED:
			  CLS1_SendStr("SW4\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 5
			case EVNT_SW5_PRESSED:
			  CLS1_SendStr("SW5\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 6
			case EVNT_SW6_PRESSED:
			  CLS1_SendStr("SW6\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		#if PL_NOF_KEYS >= 7
			case EVNT_SW7_PRESSED:
			  CLS1_SendStr("SW7\r\n", CLS1_GetStdio()->stdOut);
			  break;
		#endif

		default:
		break;
	}
}


void APP_DebugPrint(unsigned char *str) {
#if PL_HAS_SHELL
  SHELL_SendString(str);
#endif
}

/*!
 * \brief Application main 'task'.
 */
static void APP_Task(void)
{
	EVNT_SetEvent(EVNT_STARTUP);	/* set startup event */
	for(;;){
		EVNT_HandleEvent(APP_HandleEvents);
		WAIT1_WaitOSms(100/portTICK_RATE_MS);	/* wait some time */
	#if PL_HAS_KEYS && PL_NOF_KEYS>0
		KEY_Scan(); /* scan keys */
	#endif

	}
}

void run_tasks(void){
	APP_Task();
}

void initApplication()
{
	PL_Init();
	SQUEUE_Init();
	RTOS_Init();

}

void runApplication()
{
	#if configUSE_TRACE_HOOKS
	  if (RTOSTRC1_uiTraceStart()==0) {
		for(;;){} /* failed to start trace */
	  }
	#endif

	RTOS_Run();		/* never runs further */
	//APP_Task(); 	/* never runs further */

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

