/**
 * \file
 * \brief Shell Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing to the Shell.
 */

#include "Platform.h"
#if PL_HAS_SHELL_QUEUE
#include "ShellQueue.h"
#include "FRTOS1.h"
#include "Timer.h"

static xQueueHandle SQUEUE_Queue;

#define SQUEUE_LENGTH      32 /* items in queue, that's my buffer size */
#define SQUEUE_ITEM_SIZE   1  /* each item is a single character */

void SQUEUE_SendString(const unsigned char *str) {
	while(*str!='\0'){
		FRTOS1_xQueueSendToBack(SQUEUE_Queue,str,100/portTICK_RATE_MS); /* (Queue,pointer to date, ticks to wait*/
	}

}

unsigned char SQUEUE_ReceiveChar(void) {
	unsigned char ch;
	portBASE_TYPE res;
	res = FRTOS1_xQueueReceive(SQUEUE_Queue,&ch,0);

	if(res = errQUEUE_EMPTY){
		return '\0';
	}else{
		return ch;
	}
}

unsigned short SQUEUE_NofElements(void) {
  return (unsigned short)FRTOS1_uxQueueMessagesWaiting(SQUEUE_Queue);
}

void SQUEUE_Deinit(void) {
  FRTOS1_vQueueUnregisterQueue(SQUEUE_Queue);
  FRTOS1_vQueueDelete(SQUEUE_Queue);
  SQUEUE_Queue = NULL;
}

void SQUEUE_Init(void) {
  SQUEUE_Queue = FRTOS1_xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  FRTOS1_vQueueAddToRegistry(SQUEUE_Queue, "ShellQueue");
}
#endif /* PL_HAS_SHELL_QUEUE */
