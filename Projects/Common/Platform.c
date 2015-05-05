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
#include "Buzzer.h"
#include "Keys.h"
#include "Trigger.h"
#include "Debounce.h"
#include "Shell.h"
#include "Sem.h"
#include "Reflectance.h"
#include "IFsh1.h"
#include "Motor.h"
#include "MCP4728.h"
#include "Pid.h"
#include "Tacho.h"
#include "Drive.h"
#include "Zumo.h"
#include "Ultrasonic.h"
#include "RNET1.h"
#include "Accel.h"

void PL_Init(void)
{
#if PL_HAS_LED
	LED_Init();
#endif
#if PL_HAS_EVENTS
	EVNT_Init();
#endif
#if PL_HAS_BUZZER
#endif
#if PL_HAS_KEYS
	KEY_Init();
#endif
#if PL_HAS_TRIGGER
	TRG_Init();
#endif
#if PL_HAS_DEBOUNCE
  DBNC_Init();
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_SEMAPHORE
  SEM_Init();
#endif
#if PL_HAS_LINE_SENSOR
  REF_Init();
#endif
#if PL_HAS_CONFIG_NVM
  IFsh1_Init();
#endif
#if PL_HAS_MOTOR
  MOT_Init();
#endif
#if PL_HAS_MCP4728
  MCP4728_Init();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Init();
#endif
#if PL_HAS_PID
  PID_Init();
#endif
#if PL_HAS_DRIVE
  DRV_Init();
#endif
#if ZUMO_IN_BATTLE_MODE && PL_IS_ROBO
  ZUMO_Init();
#endif
#if PL_HAS_ACCEL
  ACCEL_Init();
#endif
#if PL_HAS_ULTRASONIC
  US_Init();
#endif
#if PL_HAS_RADIO
  RNET1_Init();
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
#if PL_HAS_TRIGGER
	TRG_Deinit();
#endif
#if PL_HAS_SHELL
  SHELL_Deinit();
#endif
}


/*!
** @}
*/

