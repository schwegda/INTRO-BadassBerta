/**
 * \file
 * \brief Shell (command line) interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a command line interface to the application.
 */

#ifndef SHELL_H_
#define SHELL_H_

/*!
 * \brief Hook called before parsing a command in the shell table
 * \param cmd Command parsed
 */
void SHELL_OnBeforeIterateCmd(const uint8_t *cmd);

/*!
 * \brief Hook called after parsing a command in the shell table
 * \param cmd Command parsed
 */
void SHELL_OnAfterIterateCmd(const uint8_t *cmd);

/*!
 * \brief Sends a string to the shell/console stdout
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*! \brief Shell Module initialization, creates Shell task */
void SHELL_Init(void);

/*! \brief Shell driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
