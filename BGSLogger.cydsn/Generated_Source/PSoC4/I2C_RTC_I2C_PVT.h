/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_I2C_RTC_H)
#define CY_SCB_I2C_PVT_I2C_RTC_H

#include "I2C_RTC_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 I2C_RTC_state; /* Current state of I2C FSM */

#if(I2C_RTC_I2C_SLAVE_CONST)
    extern volatile uint8 I2C_RTC_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * I2C_RTC_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  I2C_RTC_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  I2C_RTC_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * I2C_RTC_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  I2C_RTC_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  I2C_RTC_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  I2C_RTC_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   I2C_RTC_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (I2C_RTC_I2C_SLAVE_CONST) */

#if(I2C_RTC_I2C_MASTER_CONST)
    extern volatile uint16 I2C_RTC_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  I2C_RTC_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * I2C_RTC_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  I2C_RTC_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  I2C_RTC_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * I2C_RTC_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  I2C_RTC_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  I2C_RTC_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  I2C_RTC_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (I2C_RTC_I2C_MASTER_CONST) */

#if (I2C_RTC_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*I2C_RTC_customAddressHandler) (void);
#endif /* (I2C_RTC_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(I2C_RTC_SCB_MODE_I2C_CONST_CFG)
    void I2C_RTC_I2CInit(void);
#endif /* (I2C_RTC_SCB_MODE_I2C_CONST_CFG) */

void I2C_RTC_I2CStop(void);
void I2C_RTC_I2CSaveConfig(void);
void I2C_RTC_I2CRestoreConfig(void);

#if(I2C_RTC_I2C_MASTER_CONST)
    void I2C_RTC_I2CReStartGeneration(void);
#endif /* (I2C_RTC_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_I2C_RTC_H) */


/* [] END OF FILE */
