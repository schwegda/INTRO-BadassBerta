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


typedef enum{
	ZUMO_STATE_IDLE,
	ZUMO_STATE_START,
	ZUMO_STATE_LINEDETECTION,
	ZUMO_STATE_TURN,
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

	if(battleDisabled || ZUMO_FatalCrash()){
		currentState = ZUMO_STATE_IDLE;
		battleDisabled = TRUE;
		DRV_SetSpeed(0x00,0x00);
	}else{
		uint16 val;
		switch(currentState){
		case ZUMO_STATE_IDLE:
			BUZ_Beep(100,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(200,500);
			WAIT1_WaitOSms(500);
			BUZ_Beep(300,500);
			WAIT1_WaitOSms(500);
			currentState = ZUMO_STATE_START;
			break;
		case ZUMO_STATE_START:
			DRV_SetSpeed(0x2000,0x2000);
			currentState = ZUMO_STATE_LINEDETECTION;
			break;
		case ZUMO_STATE_LINEDETECTION:
			val = REF_GetLineValue();
			if(val > 500 && val< 3000){
				DRV_SetSpeed(-0x300,-0x300);
				WAIT1_WaitOSms(500);
				DRV_SetSpeed(0x300,-0x300);
				WAIT1_WaitOSms(1000);
				currentState = ZUMO_STATE_TURN;
			}else if(val > 3000 && val < 6000){
				DRV_SetSpeed(-0x300,-0x300);
				WAIT1_WaitOSms(500);
				DRV_SetSpeed(-0x300,0x300);
				WAIT1_WaitOSms(1000);
				currentState = ZUMO_STATE_TURN;
			}
			break;
		case ZUMO_STATE_TURN:
			currentState = ZUMO_STATE_START;
			break;
		}
	}
}

static portTASK_FUNCTION(Zumo_Task, pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;){
		ZUMO_Battle_Mode();

		WAIT1_WaitOSms(2);

	}

}

static void ZUMO_BattleDisable(bool battleDisable){
	battleDisabled = battleDisable;
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
    ZUMO_BattleDisable(FALSE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"zumo battle off")==0) {
    ZUMO_BattleDisable(TRUE);
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
#endif
}

#endif
