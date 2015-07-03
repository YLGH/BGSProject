/*******************************************************************************
* File Name: TDOA_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TDOA.h"

static TDOA_backupStruct TDOA_backup;


/*******************************************************************************
* Function Name: TDOA_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TDOA_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TDOA_SaveConfig(void) 
{
    #if (!TDOA_UsingFixedFunction)
        TDOA_backup.TimerUdb = TDOA_ReadCounter();
        TDOA_backup.InterruptMaskValue = TDOA_STATUS_MASK;
        #if (TDOA_UsingHWCaptureCounter)
            TDOA_backup.TimerCaptureCounter = TDOA_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TDOA_UDB_CONTROL_REG_REMOVED)
            TDOA_backup.TimerControlRegister = TDOA_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TDOA_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TDOA_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TDOA_RestoreConfig(void) 
{   
    #if (!TDOA_UsingFixedFunction)

        TDOA_WriteCounter(TDOA_backup.TimerUdb);
        TDOA_STATUS_MASK =TDOA_backup.InterruptMaskValue;
        #if (TDOA_UsingHWCaptureCounter)
            TDOA_SetCaptureCount(TDOA_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TDOA_UDB_CONTROL_REG_REMOVED)
            TDOA_WriteControlRegister(TDOA_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TDOA_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TDOA_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TDOA_Sleep(void) 
{
    #if(!TDOA_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TDOA_CTRL_ENABLE == (TDOA_CONTROL & TDOA_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TDOA_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TDOA_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TDOA_Stop();
    TDOA_SaveConfig();
}


/*******************************************************************************
* Function Name: TDOA_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TDOA_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TDOA_Wakeup(void) 
{
    TDOA_RestoreConfig();
    #if(!TDOA_UDB_CONTROL_REG_REMOVED)
        if(TDOA_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TDOA_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
