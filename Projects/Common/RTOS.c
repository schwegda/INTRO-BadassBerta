/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Application.h"

/*! \brief Task which handles the events
 *
 *	detailed description is the following...
 */
static void Task_HandleEvents (void *pvParams)
{
	(void)pvParams;
	for(;;){
		run_tasks();
	}

}


void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();
  /* does usually not return here */
}

void RTOS_Init(void) {

	if (FRTOS1_xTaskCreate(Task_HandleEvents, (signed portCHAR *)"Handle_Tasks", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
	for(;;){}
	}
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
