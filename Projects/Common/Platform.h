/*
 * Platform.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef PL_BOARD_IS_FRDM
	#define PL_NOF_LEDS 3
	/* FRDM Board has 3 LED's (RGB)*/
#elif PL_BOARD_IS_ROBO
	#define PL_NOF_LEDS 2
	/*Robot has 2 LEDs*/
#else
	#error "This is not BadassBerta!!"
#endif

void PL_Init(void);
void PL_Deinit(void);


#endif /* PLATFORM_H_ */
