/*
 * Zumo.c
 *
 *  Created on: 28.04.2015
 *      Author: David Schwegler
 */


#include "Zumo.h"
#include "FRTOS1.h"
#include "Drive.h"
#include "Reflectance.h"
#include "WAIT1.h"
#include "Accel.h"
#if PL_IS_ROBO
#include "Buzzer.h"
#include "Ultrasonic.h"


#define ZUMO_ATTACK_SPEED	(0x1500)
#define ZUMO_TURN_SPEED		(0x800)
#define ZUMO_SEARCH_SPEED	(0x600)
#define ZUMO_FALLOUT_SPEED	(0x1000)

typedef enum{
	ZUMO_STATE_IDLE,
	ZUMO_STATE_STARTUP,
	ZUMO_STATE_DEF_POS,
	ZUMO_STATE_DRIVE,
	ZUMO_STATE_OPP_DETCT,
	ZUMO_STATE_WHITE_LINE,
}ZUMO_STATES;

static ZUMO_STATES currentState;
static bool battleDisabled = TRUE;

static bool ZUMO_FatalCrash(void){
	int16_t x;
	int16_t y;
	int16_t z;
	bool isEnabled;
	ACCEL_isEnabled(&isEnabled);
	if(!isEnabled){
		ACCEL_Enable();
	}
	ACCEL_GetValues(&x,&y,&z);
	if(z <= -2000){
		return TRUE;
	}
	return FALSE;
}


static void ZUMO_Battle_Mode(void){

	uint16 val;
	uint16 cm;

	switch(currentState){
		case ZUMO_STATE_IDLE:
			if(!battleDisabled){
				currentState = ZUMO_STATE_STARTUP;
			}
			break;
		case ZUMO_STATE_STARTUP:
			BUZ_Beep(100,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(200,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(300,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(400,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(100,500);
			WAIT1_WaitOSms(1000);
			BUZ_Beep(100,500);
			WAIT1_WaitOSms(1000);
			BUZ_Beep(100,500);
			WAIT1_WaitOSms(1000);
			currentState = ZUMO_STATE_DEF_POS;
			break;
		case ZUMO_STATE_DEF_POS:
			DRV_SetSpeed(-ZUMO_FALLOUT_SPEED,ZUMO_FALLOUT_SPEED);
			WAIT1_WaitOSms(200);
			DRV_SetSpeed(ZUMO_FALLOUT_SPEED,ZUMO_FALLOUT_SPEED);
			WAIT1_WaitOSms(200);
			DRV_SetSpeed(ZUMO_FALLOUT_SPEED,-ZUMO_FALLOUT_SPEED);
			WAIT1_WaitOSms(200);
			currentState = ZUMO_STATE_DRIVE;
			break;
		case ZUMO_STATE_DRIVE:
			DRV_SetSpeed(ZUMO_ATTACK_SPEED,ZUMO_ATTACK_SPEED);
			currentState = ZUMO_STATE_WHITE_LINE;
			break;
		case ZUMO_STATE_OPP_DETCT:
			cm = US_GetLastCentimeterValue();
			if(cm > 0 && cm <= 70){
				currentState = ZUMO_STATE_DRIVE;
			}

			break;
		case ZUMO_STATE_WHITE_LINE:
			val = REF_GetLineValue();
			if(ZUMO_FatalCrash()){
				ZUMO_LeaveBattleMode();
			}

			if(val > 500 && val< 3000){			//detect which side line was detected
				DRV_SetSpeed(-ZUMO_TURN_SPEED,-ZUMO_TURN_SPEED);
				WAIT1_WaitOSms(500);
				DRV_SetSpeed(ZUMO_SEARCH_SPEED,-ZUMO_SEARCH_SPEED);

				currentState = ZUMO_STATE_OPP_DETCT;
			}else if(val > 3000 && val < 6000){
				DRV_SetSpeed(-ZUMO_TURN_SPEED,-ZUMO_TURN_SPEED);
				WAIT1_WaitOSms(500);
				DRV_SetSpeed(-ZUMO_SEARCH_SPEED,ZUMO_SEARCH_SPEED);

				currentState = ZUMO_STATE_OPP_DETCT;
			}
			break;
		}
}

static portTASK_FUNCTION(Zumo_Task, pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;){
		ZUMO_Battle_Mode();
		WAIT1_WaitOSms(5);
	}

}

static portTASK_FUNCTION(Meaure_Task, pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;){
		US_Measure_us();
		WAIT1_WaitOSms(40);
	}

}

void ZUMO_EnterBattleMode(void){
	battleDisabled = FALSE;
}

void ZUMO_LeaveBattleMode(void){
	battleDisabled = TRUE;
	currentState = ZUMO_STATE_IDLE;
	DRV_SetSpeed(0x00,0x00);
}

bool ZUMO_isBattleDisabled(void){
	return battleDisabled;
}


static void ZUMO_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"zumo", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  battle", battleDisabled?(unsigned char*)"off\r\n":(unsigned char*)"on\r\n", io->stdOut);
}

static void ZUMO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"zumo", (unsigned char*)"Group of drive commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  battle (on|off)", (unsigned char*)"Turns zumo in Battle Mode\r\n", io->stdOut);
}

uint8_t ZUMO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  int32_t val32;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"zumo help")==0) {
    ZUMO_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"zumo status")==0) {
    ZUMO_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"zumo battle on")==0) {
    ZUMO_EnterBattleMode();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"zumo battle off")==0) {
    ZUMO_LeaveBattleMode();
    REF_SetCalinrationFlag(TRUE);
    *handled = TRUE;
  }

  return res;
}


void ZUMO_Deinit(void) {
   /* nothing needed */
}

void ZUMO_Init(void) {

#if ZUMO_IN_BATTLE_MODE
  if (FRTOS1_xTaskCreate(
        Zumo_Task,  /* pointer to the task */
        "Zumo", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+100, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }

  if (FRTOS1_xTaskCreate(
          Meaure_Task,  /* pointer to the task */
          "Ultrasonic_Task", /* task name for kernel awareness debugging */
          configMINIMAL_STACK_SIZE, /* task stack size */
          (void*)NULL, /* optional task startup argument */
          tskIDLE_PRIORITY+1,  /* initial priority */
          (xTaskHandle*)NULL /* optional task handle to create */
        ) != pdPASS) {
      /*lint -e527 */
      for(;;){} /* error! probably out of memory */
      /*lint +e527 */
    }
#endif
}

#endif
