/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LED_1.h"
#include "LED_1.h"
#include "LEDpin1.h"
#include "BitIoLdd2.h"
#include "LED_2.h"
#include "LED_2.h"
#include "LEDpin2.h"
#include "BitIoLdd3.h"
#include "LED_3.h"
#include "LED_3.h"
#include "LEDpin3.h"
#include "BitIoLdd4.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "KEY_GR.h"
#include "keyPin1.h"
#include "KeyISRpin1.h"
#include "ExtIntLdd1.h"
#include "TRG1.h"
#include "CS1.h"
#include "KEY_B.h"
#include "ExtIntLdd2.h"
#include "KEY_R.h"
#include "ExtIntLdd3.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void Cpu_OnNMIINT(void);


void KEY_GR_OnKeyPressed(byte keys);
/*
** ===================================================================
**     Event       :  KEY_GR_OnKeyPressed (module Events)
**
**     Component   :  KEY_GR [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY_GR_OnKeyReleased(byte keys);
/*
** ===================================================================
**     Event       :  KEY_GR_OnKeyReleased (module Events)
**
**     Component   :  KEY_GR [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY_B_OnKeyPressed(byte keys);
/*
** ===================================================================
**     Event       :  KEY_B_OnKeyPressed (module Events)
**
**     Component   :  KEY_B [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY_R_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  KEY_R_OnInterrupt (module Events)
**
**     Component   :  KEY_R [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void KEY_B_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  KEY_B_OnInterrupt (module Events)
**
**     Component   :  KEY_B [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
