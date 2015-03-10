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
**      This module is our main loop programm so you dont have to modify main.c
** @detail
**
*/


#include "PE_Types.h"
#include "../../Common/Platform.h"
#include "../../Common/LED.h"
#include "Application.h"
#include "WAIT1.h"

void initApplication()
{
	PL_Init();
	PL_Deinit();
}

void mainApplication()
{
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
}

void deinitApplication()
{
	/*! do nothing*/
}

