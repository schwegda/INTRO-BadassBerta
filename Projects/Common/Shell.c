/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#include "FRTOS1.h"
#if PL_HAS_USB_CDC
  #include "USB1.h"
#endif
#if PL_HAS_BLUETOOTH
  #include "BT1.h"
#endif
#if PL_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif
#if PL_HAS_LINE_SENSOR
  #include "Reflectance.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_QUAD_CALIBRATION
	#include "QuadCalib.h"
	#include "Q4CRight.h"
	#include "Q4CLeft.h"
#endif
#if PL_HAS_MCP4728
  #include "MCP4728.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_DRIVE
	#include "Drive.h"
#endif
#if PL_HAS_PID
	#include "Pid.h"
	#include "Zumo.h"
#endif
#include "MMA1.h"
#include "Ultrasonic.h"

#if PL_HAS_RADIO
  #include "RNET1.h"
  #include "RNet_App.h"
  #include "RNetConf.h"
#endif
#if RNET_CONFIG_REMOTE_STDIO
  #include "RStdIO.h"
#endif
#include "Remote.h"

/* forward declaration */
static uint8_t SHELL_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand, /* Processor Expert Shell component, is first in list */
  SHELL_ParseCommand, /* our own module parser */
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand, /* FreeRTOS shell parser */
#endif
#if PL_HAS_BLUETOOTH
#if BT1_PARSE_COMMAND_ENABLED
  BT1_ParseCommand,
#endif
#endif
#if PL_HAS_LINE_SENSOR
  REF_ParseCommand,
#endif
#if PL_HAS_MOTOR
  MOT_ParseCommand,
#endif
#if PL_HAS_MCP4728
  MCP4728_ParseCommand,
#endif
#if PL_HAS_QUAD_CALIBRATION
  QUADCALIB_ParseCommand,
  Q4CRight_ParseCommand,
  Q4CLeft_ParseCommand,
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_ParseCommand,
#endif
#if PL_HAS_DRIVE
  DRV_ParseCommand,
#endif
#if PL_HAS_PID
  PID_ParseCommand,
  ZUMO_ParseCommand,
#endif
#if PL_HAS_ULTRASONIC
  US_ParseCommand,
#endif
#if PL_HAS_ACCEL
  MMA1_ParseCommand,
#endif
#if PL_HAS_RADIO
  RNET1_ParseCommand,
  RNETA_ParseCommand,
#endif
#if PL_HAS_REMOTE
  REMOTE_ParseCommand,
#endif
  NULL /* Sentinel */
};

static uint32_t SHELL_val; /* used as demo value for shell */

void SHELL_SendString(unsigned char *msg) {
#if PL_HAS_SHELL_QUEUE
  /*! \todo Implement function using queues */
  SQUEUE_SendString(msg);
#else
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
#endif
}

/*!
 * \brief Prints the help text to the console
 * \param io StdIO handler
 * \return ERR_OK or failure code
 */
static uint8_t SHELL_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("Shell", "Shell commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  val <num>", "Assign number value\r\n", io->stdOut);
  return ERR_OK;
}

/*!
 * \brief Prints the status text to the console
 * \param io StdIO handler
 * \return ERR_OK or failure code
 */
static uint8_t SHELL_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[16];

  CLS1_SendStatusStr("Shell", "\r\n", io->stdOut);
  UTIL1_Num32sToStr(buf, sizeof(buf), SHELL_val);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  val", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t SHELL_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Shell help")==0) {
    *handled = TRUE;
    return SHELL_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "Shell status")==0) {
    *handled = TRUE;
    return SHELL_PrintStatus(io);
  } else if (UTIL1_strncmp(cmd, "Shell val ", sizeof("Shell val ")-1)==0) {
    p = cmd+sizeof("Shell val ")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK) {
      SHELL_val = val;
      *handled = TRUE;
    } else {
      return ERR_FAILED; /* wrong format of command? */
    }
  }
  return ERR_OK;
}

#if PL_HAS_BLUETOOTH
/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};
#endif

#if PL_HAS_USB_CDC /* USB-CDC stdio */
static bool CDC_StdIOKeyPressed(void) {
  return (bool)((CDC1_GetCharsInRxBuf()==0U) ? FALSE : TRUE); /* true if there are characters in receive buffer */
}

static void CDC_StdIOReadChar(uint8_t *c) {
  if (CDC1_GetChar((uint8_t *)c) != ERR_OK) {
    /* failed to receive character: return a zero character */
    *c = '\0';
  }
}

static void CDC_StdIOSendChar(uint8_t ch) {
  while (CDC1_SendChar((uint8_t)ch)==ERR_TXFULL){} /* Send char */
}

static CLS1_ConstStdIOType CDC_stdio = {
  (CLS1_StdIO_In_FctType)CDC_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)CDC_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)CDC_StdIOSendChar, /* stderr */
  CDC_StdIOKeyPressed /* if input is not empty */
};
#endif

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_USB_CDC
  static unsigned char cdc_buf[48];
#endif
#if PL_HAS_BLUETOOTH
  static unsigned char bluetooth_buf[48];
#endif
  static unsigned char localConsole_buf[48];
#if CLS1_DEFAULT_SERIAL
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
#endif

#if RNET_CONFIG_REMOTE_STDIO
  static unsigned char radio_cmd_buf[48];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
  
  (void)pvParameters; /* not used */
#if PL_HAS_USB_CDC
  cdc_buf[0] = '\0';
#endif
#if PL_HAS_BLUETOOTH
  bluetooth_buf[0] = '\0';
#endif
  localConsole_buf[0] = '\0';
#if RNET_CONFIG_REMOTE_STDIO
  radio_cmd_buf[0] = '\0';
#endif

#if CLS1_DEFAULT_SERIAL
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
#endif
  for(;;) {
#if CLS1_DEFAULT_SERIAL
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
#endif
#if PL_HAS_USB_CDC
    (void)CLS1_ReadAndParseWithCommandTable(cdc_buf, sizeof(cdc_buf), &CDC_stdio, CmdParserTable);
#endif
#if PL_HAS_BLUETOOTH
    (void)CLS1_ReadAndParseWithCommandTable(bluetooth_buf, sizeof(bluetooth_buf), &BT_stdio, CmdParserTable);
#endif
#if RNET_CONFIG_REMOTE_STDIO
    RSTDIO_Print(ioLocal); /* dispatch incoming messages */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
#if PL_HAS_SHELL_QUEUE
    {
      /*! \todo Handle shell queue */
      unsigned char ch;

      while((ch=SQUEUE_ReceiveChar()) && ch!='\0') {
        ioLocal->stdOut(ch);
#if PL_HAS_BLUETOOTH
        BT_stdio.stdOut(ch); /* copy on Bluetooth */
#endif
#if PL_HAS_USB_CDC
        CDC_stdio.stdOut(ch); /* copy to USB_CDC */
#endif
      }
    }
#endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

void SHELL_Init(void) {
#if !CLS1_DEFAULT_SERIAL && PL_HAS_BLUETOOTH
  (void)CLS1_SetStdio(&BT_stdio); /* use the Bluetooth stdio as default */
#endif
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

void SHELL_Deinit(void) {
}

#endif /* PL_HAS_SHELL */
