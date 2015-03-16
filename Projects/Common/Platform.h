/*
 * Platform.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */


#include "PE_Types.h"


#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_HAS_LED (1)		/*!<Set to 0 if there are no LED's>*/
#define PL_HAS_EVENTS (1)	/*!<Set to 0 if there are no Events>*/
#define PL_HAS_TIMER (1)	/*!<Set to 0 if there are no Timers used>*/

#define PL_HAS_KEYS           (1)
  /*!< Set to 1 to enable keys, 0 otherwise */
#define PL_HAS_KBI            (1)
  /*!< Set to 1 to enable key interrupt support, 0 otherwise */
#define PL_HAS_KBI_NMI        (1 && PL_IS_FRDM && PL_HAS_JOYSTICK)
  /*!< Set to 1 for special case on NMI/PTA pin on FRDM board, 0 otherwise */
#define PL_HAS_MEALY          (1 && PL_NOF_LEDS>=1 && PL_NOF_KEYS>=1)
  /*!< Set to 1 to enable Mealy sequential state machine, 0 otherwise */
#define PL_HAS_RESET_KEY      (0 && PL_IS_FRDM && PL_HAS_KEYS)
  /*!< Set to 1 to use reset switch on FRDM as button, 0 otherwise */
#define PL_HAS_JOYSTICK       (1 && PL_IS_FRDM && PL_HAS_KEYS)
  /*!< Set to 1 to enable joystick shield support, 0 otherwise */


#ifdef PL_BOARD_IS_FRDM
	#define PL_KEY_POLLED_KEY1    (0)
	#define PL_KEY_POLLED_KEY2    (0)
	#define PL_KEY_POLLED_KEY3    (0)
	#define PL_KEY_POLLED_KEY4    (0)
	#define PL_KEY_POLLED_KEY5    (1)
	#define PL_KEY_POLLED_KEY6    (1)
	#define PL_KEY_POLLED_KEY7    (0)

	#define PL_NOF_LEDS (3)
	/* FRDM Board has 3 LED's (RGB)*/
#elif PL_BOARD_IS_ROBO
	#define PL_NOF_LEDS (2)
	/*Robot has 2 LEDs*/
	#define PL_HAS_BUZZER (1)
#else
	#error "This is not BadassBerta!!"
#endif


void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
