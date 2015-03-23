/* ###################################################################
**     Filename    : Events.c
**     Project     : FRDM
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-17, 11:29, # CodeGen: 0
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

#include "../../Common/Timer.h"
#include "../../Common/Keys.h"
#include "../../Common/Trigger.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
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
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
#if PL_HAS_TIMER
	TMR_OnInterrupt();
#endif
}

/*
** ===================================================================
**     Event       :  SW7_OnInterrupt (module Events)
**
**     Component   :  SW7 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW7_OnInterrupt(void)
{
	if(SW7_GetVal() == 0){
		  KEY_OnInterrupt(KEY_BTN7);
	  }
}

/*
** ===================================================================
**     Event       :  SW4_OnInterrupt (module Events)
**
**     Component   :  SW4 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW4_OnInterrupt(void)
{
	if(SW4_GetVal() == 0){
		  KEY_OnInterrupt(KEY_BTN4);
	  }
}


/*
** ===================================================================
**     Event       :  SW3_OnInterrupt (module Events)
**
**     Component   :  SW3 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW3_OnInterrupt(void)
{
	if(PORT_PDD_GetPinInterruptFlag(PORTA_BASE_PTR, ExtIntLdd5_PIN_INDEX))
	{
		PORT_PDD_ClearPinInterruptFlag(PORTA_BASE_PTR,  ExtIntLdd5_PIN_INDEX);
		KEY_OnInterrupt(KEY_BTN3);
	}
}


/*
** ===================================================================
**     Event       :  SW2_OnInterrupt (module Events)
**
**     Component   :  SW2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW2_OnInterrupt(void)
{
	if(SW2_GetVal() == 0){
		  KEY_OnInterrupt(KEY_BTN2);
	  }
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
  if(SW1_GetVal() == 0){
	  KEY_OnInterrupt(KEY_BTN1);
  }
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
