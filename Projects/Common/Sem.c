/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"
#include "WAIT1.h"

static xSemaphoreHandle MySem = NULL;

static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  for(;;) {
    /*! \todo Implement functionality */
	  if(FRTOS1_xSemaphoreTake(MySem,100) == pdTRUE){
		  LED2_Neg();
	  }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  for(;;) {
    /*! \todo Implement functionality */
	  FRTOS1_xSemaphoreGive(MySem);
	  WAIT1_WaitOSms(1000/portTICK_RATE_MS);	/* wait some time */
  }
}

void SEM_Deinit(void) {
  /* nothing */
}

/*! \brief Initializes module */
void SEM_Init(void) {
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(vSlaveTask, "Slave", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  vSemaphoreCreateBinary(MySem);
  if (MySem == NULL) {
    for(;;); /* creation failed */
  }
}
#endif /* PL_HAS_SEMAPHORE */
