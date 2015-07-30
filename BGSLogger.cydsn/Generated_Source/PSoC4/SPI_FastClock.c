/*******************************************************************************
* File Name: SPI_FastClock.c
* Version 2.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "SPI_FastClock.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: SPI_FastClock_StartEx
********************************************************************************
*
* Summary:
*  Starts the clock, aligned to the specified running clock.
*
* Parameters:
*  alignClkDiv:  The divider to which phase alignment is performed when the
*    clock is started.
*
* Returns:
*  None
*
*******************************************************************************/
void SPI_FastClock_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((SPI_FastClock_CMD_REG & SPI_FastClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    SPI_FastClock_CMD_REG =
        ((uint32)SPI_FastClock__DIV_ID << SPI_FastClock_CMD_DIV_SHIFT)|
        (alignClkDiv << SPI_FastClock_CMD_PA_DIV_SHIFT) |
        (uint32)SPI_FastClock_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: SPI_FastClock_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/

void SPI_FastClock_Start(void)
{
    /* Set the bit to enable the clock. */
    SPI_FastClock_ENABLE_REG |= SPI_FastClock__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: SPI_FastClock_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void SPI_FastClock_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((SPI_FastClock_CMD_REG & SPI_FastClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    SPI_FastClock_CMD_REG =
        ((uint32)SPI_FastClock__DIV_ID << SPI_FastClock_CMD_DIV_SHIFT)|
        ((uint32)SPI_FastClock_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    SPI_FastClock_ENABLE_REG &= (uint32)(~SPI_FastClock__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: SPI_FastClock_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void SPI_FastClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (SPI_FastClock__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = SPI_FastClock_DIV_REG & 
                    (uint32)(~(uint32)(SPI_FastClock_DIV_INT_MASK | SPI_FastClock_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  SPI_FastClock_DIV_INT_SHIFT) & SPI_FastClock_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << SPI_FastClock_DIV_FRAC_SHIFT) & SPI_FastClock_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = SPI_FastClock_DIV_REG & (uint32)(~(uint32)SPI_FastClock__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* SPI_FastClock__FRAC_MASK || CYREG_PERI_DIV_CMD */

    SPI_FastClock_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: SPI_FastClock_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 SPI_FastClock_GetDividerRegister(void)
{
    return (uint16)((SPI_FastClock_DIV_REG & SPI_FastClock_DIV_INT_MASK)
        >> SPI_FastClock_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: SPI_FastClock_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 SPI_FastClock_GetFractionalDividerRegister(void)
{
#if defined (SPI_FastClock__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((SPI_FastClock_DIV_REG & SPI_FastClock_DIV_FRAC_MASK)
        >> SPI_FastClock_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* SPI_FastClock__FRAC_MASK */
}


/* [] END OF FILE */
