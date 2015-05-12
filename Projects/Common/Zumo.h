/*
 * Zumo.h
 *
 *  Created on: 28.04.2015
 *      Author: David Schwegler
 */

#ifndef ZUMO_H_
#define ZUMO_H_

#include "Platform.h"
#include "CLS1.h"

void ZUMO_Deinit(void);
void ZUMO_Init(void);

void ZUMO_EnterBattleMode(void);
void ZUMO_LeaveBattleMode(void);
bool ZUMO_isBattleDisabled(void);

uint8_t ZUMO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

#endif /* ZUMO_H_ */
