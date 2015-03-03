/* ###################################################################
**     Filename    : LED.c
**     Project     : INTRO
**     Processor   : MK22FX512VLQ12 / MKL25Z128VLK4
**     Version     : Driver 01.0
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-1, 08:21, # CodeGen: 0
**     Abstract    :
**         LED Interface implementation.
**         This module Interface that make possible to use Code on Robot and FRDM Board
**     Settings    :
**     Contents    :
**     		void LED_Init(void)
**			void LED_Deinit(void)
**
** ###################################################################*/
/*!
** @file LED.c
** @version 01.00
** @brief
**  	LED Interface implementation.
**      This module Interface that make possible to use Code on Robot and FRDM Board.
*/
/*!
**  @addtogroup LED_module LED module documentation
**  @{
*/
/* MODULE Led */

#include "LED.h"

/*!
 * \brief Initialize all LED.
 */
void LED_Init(void) {
  /* all LED's off by default */

	LED1_Off();
	LED2_Off();
	LED3_Off();
}

void LED_Deinit(void) {
  /* nothing to do */
}

/*@}
 */
