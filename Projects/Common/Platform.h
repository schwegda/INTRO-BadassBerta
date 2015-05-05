/*
 * Platform.h
 *
 *  Created on: 02.03.2015
 *      Author: Alexander
 */


#include "PE_Types.h"


#ifndef PLATFORM_H_
#define PLATFORM_H_

#define ZUMO_IN_BATTLE_MODE (1)	/*Set to 1 for Zumo Battle

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_FRDM   (defined(PL_BOARD_IS_FRDM))
  /*!< Macro is defined through compiler option for the FRDM board */
#define PL_IS_ROBO   (defined(PL_BOARD_IS_ROBO))
  /*!< Macro is defined through compiler option for the Robot board */


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
#define PL_HAS_TRIGGER		  (1)
  /*!< Set to 1 for trigger enabled, 0 otherwise */
#define PL_HAS_DEBOUNCE	(1)
  /*!< We debounce the buttons*/
#define PL_HAS_RTOS (1)
	/*!< Set to 1 to use RTOS */
#define PL_HAS_SHELL (1)
	/*! Set to 1 to use Command-Shell*/
#define PL_HAS_USB_CDC (1)
	/*! Set to 1 to use Command-Shell over usb CDC*/
#define PL_HAS_SHELL_QUEUE (1)
	/*! Set to 1 to use Shell Queue */
#define PL_HAS_SEMAPHORE 	(1)
	/*! Set to 1 to use Semaphore */
#define PL_HAS_CONFIG_NVM 	(1)
	/*! Set when using internal FLASH to store settings */
#define PL_HAS_ACCEL (1)

#define PL_HAS_RADIO (1)


/* if keys are using interrupts or are polled */
#if PL_IS_FRDM
  #define PL_KEY_POLLED_KEY1    (0)
  #define PL_KEY_POLLED_KEY2    (0)
  #define PL_KEY_POLLED_KEY3    (0)
  #define PL_KEY_POLLED_KEY4    (0)
  #define PL_KEY_POLLED_KEY5    (1)
  #define PL_KEY_POLLED_KEY6    (1)
  #define PL_KEY_POLLED_KEY7    (0)
#elif PL_IS_ROBO
  #define PL_KEY_POLLED_KEY1    (0)
#endif

#if PL_IS_FRDM
  #if PL_HAS_JOYSTICK
    #define PL_NOF_LEDS       (2)
      /*!< FRDM board has 2 LEDs (blue is used by joystick shield/nrf24L01+ SPI CLK) */
    #define PL_NOF_KEYS       (7)
       /*!< FRDM board has no keys without joystick shield */
  #else
    #define PL_NOF_LEDS       (3)
       /*!< FRDM board has up to 3 LEDs (RGB) */
#if PL_HAS_RESET_KEY
    #define PL_NOF_KEYS       (1)
       /*!< FRDM board with using the reset button */
#else
    #define PL_NOF_KEYS       (0)
       /*!< FRDM board has no keys without joystick shield */
#endif
  #endif
#elif PL_IS_ROBO
  	#define PL_HAS_BUZZER 	(1)
  	  /*!< We have one Buzzer on the Robot Baseboard */
  	#define PL_NOF_LEDS       (2)
     /*!< We have up to 2 LED's on the robo board */
  	#define PL_NOF_KEYS       (1)
     /*!< We have up to 1 push button */
  	#define PL_HAS_BLUETOOTH 	(1)
	 /*! Set to 1 to use Bluetooth Communication*/
  	#define PL_HAS_LINE_SENSOR (1)
	 /*! Set to 1 to use the Line Sensors*/
  	#define PL_HAS_MOTOR (1)
     /*! Set to 1 to use the motors */
	#define PL_IS_INTRO_ZUMO_K22_V2 (1)
	/*! Set to 1 if use the old Zumo platform*/
	#define PL_HAS_QUAD_CALIBRATION (1)
	 /*! Set to 1 to use the quad Counter Calibration */
	#define PL_HAS_MCP4728 (1)
	 /*! Set to 1 to use the MCP4728*/
	#define PL_HAS_MOTOR_TACHO  (1)
	 /*! Set to 1 to use the Tacho*/
	#define PL_HAS_DRIVE	(1)
	/*! Set to 1 if Robot has Motors*/
	#define PL_HAS_PID	(1)
	/*! Set to 1 to use the PID-Conroller*/
	#define PL_HAS_ULTRASONIC	(1)
#else
  #error "unknown configuration?"
#endif

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
