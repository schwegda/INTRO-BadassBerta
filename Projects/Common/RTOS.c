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

static void T1(void *pvParams) {

  (void)pvParams;
  for(;;) {
    LED1_Neg();
    //FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

static void T2(void *pvParams) {

  (void)pvParams;
  for(;;) {
    LED2_Neg();
    //FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}


void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();
  /* does usually not return here */
}

void RTOS_Init(void) {
  if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(T2, (signed portCHAR *)"T2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
      for(;;){} /* error */
    }

}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
