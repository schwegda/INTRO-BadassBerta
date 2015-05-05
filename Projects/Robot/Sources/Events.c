/* ###################################################################
**     Filename    : Events.c
**     Project     : Robot
**     Processor   : MK22FX512VLQ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-23, 09:09, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "../../Common/Platform.h"
#include "../../Common/Timer.h"
#include "../../Common/Keys.h"
#include "../../Common/Ultrasonic.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK22FN1M0LQ12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SW1_OnInterrupt (module Events)
**
**     Component   :  SW1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW1_OnInterrupt(void)
{
	/*! Damit Heartbeat nicht von diesem Interrupt unterbrochen wird*/
	/*! \todo Abfrage ob Pin tatsächlich auf 1 ist nicht mehr machen? */

	/*
	if (PORT_PDD_GetPinInterruptFlag(PORTA_BASE_PTR, ExtIntLdd1_PIN_INDEX))
	  {
	     PORT_PDD_ClearPinInterruptFlag(PORTA_BASE_PTR, ExtIntLdd1_PIN_INDEX);
	     KEY_OnInterrupt(KEY_BTN1);
	  }
	  */
#if PL_HAS_KBI
  if (KEY1_Get()) {
    KEY_OnInterrupt(KEY_BTN1);
  }
#endif
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationTickHook(void)
{
  /* Called for every RTOS tick. */
	  /* Write your code here ... */
	#if PL_HAS_TIMER
		TMR_OnInterrupt();
	#endif
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  RTOSTRC1_OnTraceWrap (module Events)
**
**     Component   :  RTOSTRC1 [PercepioTrace]
**     Description :
**         Called for trace ring buffer wrap around. This gives the
**         application a chance to dump the trace buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RTOSTRC1_OnTraceWrap(void)
{
	  uint8_t buf[64];

	  RTOSTRC1_vGetGDBDumpCommand(buf, sizeof(buf), "c:\\tmp\\trc.dump");
}

/*
** ===================================================================
<<<<<<< HEAD
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/*
** ===================================================================
**     Event       :  QuadInt_OnInterrupt (module Events)
**
**     Component   :  QuadInt [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void QuadInt_OnInterrupt(void)
{
  Q4CRight_Sample();
  Q4CLeft_Sample();
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  GI2C1_OnRequestBus (module Events)
**
**     Component   :  GI2C1 [GenericI2C]
**     Description :
**         User event which will be called before accessing the I2C bus.
**         Useful for starting a critical section.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GI2C1_OnRequestBus(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  GI2C1_OnReleaseBus (module Events)
**
**     Component   :  GI2C1 [GenericI2C]
**     Description :
**         User event which will be called after accessing the I2C bus.
**         Useful for ending a critical section.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GI2C1_OnReleaseBus(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TU_US_OnCounterRestart (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU_US_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	US_EventEchoOverflow(UserDataPtr);
}

/*
** ===================================================================
**     Event       :  TU_US_OnChannel0 (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU_US_OnChannel0(LDD_TUserData *UserDataPtr)
{
	US_EventEchoCapture(UserDataPtr);
}

/*
** ===================================================================
**     Event       :  RF1_OnActivate (module Events)
**
**     Component   :  RF1 [nRF24L01]
**     Description :
**         Event called before accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RF1_OnActivate(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  RF1_OnDeactivate (module Events)
**
**     Component   :  RF1 [nRF24L01]
**     Description :
**         Event called before releasing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RF1_OnDeactivate(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  RNET1_OnRadioEvent (module Events)
**
**     Component   :  RNET1 [RNet]
**     Description :
**         Event created for various radio states, like timeout, ack
**         received, data sent, ...
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - 
**     Returns     : Nothing
** ===================================================================
*/
void RNET1_OnRadioEvent(RNET1_RadioEvent event)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
