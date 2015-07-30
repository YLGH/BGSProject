/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_SPI_PI_H)
#define CY_SCB_PVT_SPI_PI_H

#include "SPI_PI.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SPI_PI_SetI2CExtClkInterruptMode(interruptMask) SPI_PI_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SPI_PI_ClearI2CExtClkInterruptSource(interruptMask) SPI_PI_CLEAR_INTR_I2C_EC(interruptMask)
#define SPI_PI_GetI2CExtClkInterruptSource()                (SPI_PI_INTR_I2C_EC_REG)
#define SPI_PI_GetI2CExtClkInterruptMode()                  (SPI_PI_INTR_I2C_EC_MASK_REG)
#define SPI_PI_GetI2CExtClkInterruptSourceMasked()          (SPI_PI_INTR_I2C_EC_MASKED_REG)

#if (!SPI_PI_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SPI_PI_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SPI_PI_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SPI_PI_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SPI_PI_CLEAR_INTR_SPI_EC(interruptMask)
    #define SPI_PI_GetExtSpiClkInterruptSource()                 (SPI_PI_INTR_SPI_EC_REG)
    #define SPI_PI_GetExtSpiClkInterruptMode()                   (SPI_PI_INTR_SPI_EC_MASK_REG)
    #define SPI_PI_GetExtSpiClkInterruptSourceMasked()           (SPI_PI_INTR_SPI_EC_MASKED_REG)
#endif /* (!SPI_PI_CY_SCBIP_V1) */

#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SPI_PI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SPI_PI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPI_PI_CUSTOM_INTR_HANDLER)
    extern cyisraddress SPI_PI_customIntrHandler;
#endif /* !defined (CY_REMOVE_SPI_PI_CUSTOM_INTR_HANDLER) */
#endif /* (SPI_PI_SCB_IRQ_INTERNAL) */

extern SPI_PI_BACKUP_STRUCT SPI_PI_backup;

#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SPI_PI_scbMode;
    extern uint8 SPI_PI_scbEnableWake;
    extern uint8 SPI_PI_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SPI_PI_mode;
    extern uint8 SPI_PI_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SPI_PI_rxBuffer;
    extern uint8   SPI_PI_rxDataBits;
    extern uint32  SPI_PI_rxBufferSize;

    extern volatile uint8 * SPI_PI_txBuffer;
    extern uint8   SPI_PI_txDataBits;
    extern uint32  SPI_PI_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SPI_PI_numberOfAddr;
    extern uint8 SPI_PI_subAddrSize;
#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SPI_PI_SCB_MODE_I2C_RUNTM_CFG     (SPI_PI_SCB_MODE_I2C      == SPI_PI_scbMode)
    #define SPI_PI_SCB_MODE_SPI_RUNTM_CFG     (SPI_PI_SCB_MODE_SPI      == SPI_PI_scbMode)
    #define SPI_PI_SCB_MODE_UART_RUNTM_CFG    (SPI_PI_SCB_MODE_UART     == SPI_PI_scbMode)
    #define SPI_PI_SCB_MODE_EZI2C_RUNTM_CFG   (SPI_PI_SCB_MODE_EZI2C    == SPI_PI_scbMode)
    #define SPI_PI_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SPI_PI_SCB_MODE_UNCONFIG == SPI_PI_scbMode)

    /* Defines wakeup enable */
    #define SPI_PI_SCB_WAKE_ENABLE_CHECK       (0u != SPI_PI_scbEnableWake)
#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SPI_PI_CY_SCBIP_V1)
    #define SPI_PI_SCB_PINS_NUMBER    (7u)
#else
    #define SPI_PI_SCB_PINS_NUMBER    (2u)
#endif /* (!SPI_PI_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SPI_PI_H) */


/* [] END OF FILE */
