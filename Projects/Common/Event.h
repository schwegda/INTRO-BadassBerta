/*
 * Event.h
 *
 *  Created on: 10.03.2015
 *      Author: David Schwegler
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Platform.h"


#if PL_HAS_EVENTS

typedef enum EVNT_Handle {
  EVNT_INIT,            /*!< System Initialization Event */
  EVNT_STARTUP,		/*!< System Startup Event*/
  EVNT_LED_HEARTBEAT,	/*!< LED Heartbeat of the Board>*/
  EVNT_SW1_PRESSED,		/*!< SW1 is pressed>*/
  EVNT_SW2_PRESSED,		/*!< SW2 is pressed>*/
  EVNT_SW3_PRESSED,		/*!< SW3 is pressed>*/
  EVNT_SW4_PRESSED,		/*!< SW4 is pressed>*/
  EVNT_SW5_PRESSED,		/*!< SW5 is pressed>*/
  EVNT_SW6_PRESSED,		/*!< SW6 is pressed>*/
  EVNT_SW7_PRESSED,		/*!< SW7 is pressed>*/
  EVNT_NOF_EVENTS       /*!< Must be last one! */
} EVNT_Handle;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(EVNT_Handle event);

/*!
 * \brief Clears an event.
 * \param[in] event The event handle of the event to clear.
 */
void EVNT_ClearEvent(EVNT_Handle event);

/*!
 * \brief Returns the status of an event.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSet(EVNT_Handle event);

/*!
 * \brief Returns the status of an event. As a side effect, the event gets cleared.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSetAutoClear(EVNT_Handle event);

/*!
 * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
 * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
 */
void EVNT_HandleEvent(void (*callback)(EVNT_Handle));

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* PL_HAS_EVENTS */

#endif /* EVENT_H_ */
