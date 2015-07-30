/*******************************************************************************
* File Name: SPI_PI_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_PI.h"
#include "SPI_PI_PVT.h"

#if(SPI_PI_SCB_MODE_I2C_INC)
    #include "SPI_PI_I2C_PVT.h"
#endif /* (SPI_PI_SCB_MODE_I2C_INC) */

#if(SPI_PI_SCB_MODE_EZI2C_INC)
    #include "SPI_PI_EZI2C_PVT.h"
#endif /* (SPI_PI_SCB_MODE_EZI2C_INC) */

#if(SPI_PI_SCB_MODE_SPI_INC || SPI_PI_SCB_MODE_UART_INC)
    #include "SPI_PI_SPI_UART_PVT.h"
#endif /* (SPI_PI_SCB_MODE_SPI_INC || SPI_PI_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SPI_PI_SCB_MODE_I2C_CONST_CFG   && (!SPI_PI_I2C_WAKE_ENABLE_CONST))   || \
   (SPI_PI_SCB_MODE_EZI2C_CONST_CFG && (!SPI_PI_EZI2C_WAKE_ENABLE_CONST)) || \
   (SPI_PI_SCB_MODE_SPI_CONST_CFG   && (!SPI_PI_SPI_WAKE_ENABLE_CONST))   || \
   (SPI_PI_SCB_MODE_UART_CONST_CFG  && (!SPI_PI_UART_WAKE_ENABLE_CONST)))

    SPI_PI_BACKUP_STRUCT SPI_PI_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SPI_PI_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI_PI_Sleep(void)
{
#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPI_PI_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPI_PI_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI_PI_I2CSaveConfig();
        }
        else if(SPI_PI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI_PI_EzI2CSaveConfig();
        }
    #if(!SPI_PI_CY_SCBIP_V1)
        else if(SPI_PI_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI_PI_SpiSaveConfig();
        }
        else if(SPI_PI_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI_PI_UartSaveConfig();
        }
    #endif /* (!SPI_PI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SPI_PI_backup.enableState = (uint8) SPI_PI_GET_CTRL_ENABLED;

        if(0u != SPI_PI_backup.enableState)
        {
            SPI_PI_Stop();
        }
    }

#else

    #if (SPI_PI_SCB_MODE_I2C_CONST_CFG && SPI_PI_I2C_WAKE_ENABLE_CONST)
        SPI_PI_I2CSaveConfig();

    #elif (SPI_PI_SCB_MODE_EZI2C_CONST_CFG && SPI_PI_EZI2C_WAKE_ENABLE_CONST)
        SPI_PI_EzI2CSaveConfig();

    #elif (SPI_PI_SCB_MODE_SPI_CONST_CFG && SPI_PI_SPI_WAKE_ENABLE_CONST)
        SPI_PI_SpiSaveConfig();

    #elif (SPI_PI_SCB_MODE_UART_CONST_CFG && SPI_PI_UART_WAKE_ENABLE_CONST)
        SPI_PI_UartSaveConfig();

    #else

        SPI_PI_backup.enableState = (uint8) SPI_PI_GET_CTRL_ENABLED;

        if(0u != SPI_PI_backup.enableState)
        {
            SPI_PI_Stop();
        }

    #endif /* defined (SPI_PI_SCB_MODE_I2C_CONST_CFG) && (SPI_PI_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI_PI_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI_PI_Wakeup(void)
{
#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPI_PI_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPI_PI_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI_PI_I2CRestoreConfig();
        }
        else if(SPI_PI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI_PI_EzI2CRestoreConfig();
        }
    #if(!SPI_PI_CY_SCBIP_V1)
        else if(SPI_PI_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI_PI_SpiRestoreConfig();
        }
        else if(SPI_PI_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI_PI_UartRestoreConfig();
        }
    #endif /* (!SPI_PI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SPI_PI_backup.enableState)
        {
            SPI_PI_Enable();
        }
    }

#else

    #if (SPI_PI_SCB_MODE_I2C_CONST_CFG  && SPI_PI_I2C_WAKE_ENABLE_CONST)
        SPI_PI_I2CRestoreConfig();

    #elif (SPI_PI_SCB_MODE_EZI2C_CONST_CFG && SPI_PI_EZI2C_WAKE_ENABLE_CONST)
        SPI_PI_EzI2CRestoreConfig();

    #elif (SPI_PI_SCB_MODE_SPI_CONST_CFG && SPI_PI_SPI_WAKE_ENABLE_CONST)
        SPI_PI_SpiRestoreConfig();

    #elif (SPI_PI_SCB_MODE_UART_CONST_CFG && SPI_PI_UART_WAKE_ENABLE_CONST)
        SPI_PI_UartRestoreConfig();

    #else

        if(0u != SPI_PI_backup.enableState)
        {
            SPI_PI_Enable();
        }

    #endif /* (SPI_PI_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
