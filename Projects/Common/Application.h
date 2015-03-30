/*
 * Application.h
 *
 *  Created on: 10.03.2015
 *      Author: David Schwegler
 */

/*!
** @file Application.h
** @version 01.00
** @author David Schwegler, david.schwegler@stud.hslu.ch
** @brief
**  	Application main routine.
**      This module is our main loop programm so you dont have to modify main.c
** @detail
**
*/
#ifndef APPLICATION_H_
#define APPLICATION_H_

void initApplication();
void runApplication();
void deinitApplication();

void run_tasks(void);

#endif /* APPLICATION_H_ */
