/*******************************************************************************
* File Name: SPI_FastClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SPI_FastClock_H)
#define CY_CLOCK_SPI_FastClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SPI_FastClock_StartEx(uint32 alignClkDiv);
#define SPI_FastClock_Start() \
    SPI_FastClock_StartEx(SPI_FastClock__PA_DIV_ID)

#else

void SPI_FastClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SPI_FastClock_Stop(void);

void SPI_FastClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPI_FastClock_GetDividerRegister(void);
uint8  SPI_FastClock_GetFractionalDividerRegister(void);

#define SPI_FastClock_Enable()                         SPI_FastClock_Start()
#define SPI_FastClock_Disable()                        SPI_FastClock_Stop()
#define SPI_FastClock_SetDividerRegister(clkDivider, reset)  \
    SPI_FastClock_SetFractionalDividerRegister((clkDivider), 0u)
#define SPI_FastClock_SetDivider(clkDivider)           SPI_FastClock_SetDividerRegister((clkDivider), 1u)
#define SPI_FastClock_SetDividerValue(clkDivider)      SPI_FastClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SPI_FastClock_DIV_ID     SPI_FastClock__DIV_ID

#define SPI_FastClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SPI_FastClock_CTRL_REG   (*(reg32 *)SPI_FastClock__CTRL_REGISTER)
#define SPI_FastClock_DIV_REG    (*(reg32 *)SPI_FastClock__DIV_REGISTER)

#define SPI_FastClock_CMD_DIV_SHIFT          (0u)
#define SPI_FastClock_CMD_PA_DIV_SHIFT       (8u)
#define SPI_FastClock_CMD_DISABLE_SHIFT      (30u)
#define SPI_FastClock_CMD_ENABLE_SHIFT       (31u)

#define SPI_FastClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SPI_FastClock_CMD_DISABLE_SHIFT))
#define SPI_FastClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SPI_FastClock_CMD_ENABLE_SHIFT))

#define SPI_FastClock_DIV_FRAC_MASK  (0x000000F8u)
#define SPI_FastClock_DIV_FRAC_SHIFT (3u)
#define SPI_FastClock_DIV_INT_MASK   (0xFFFFFF00u)
#define SPI_FastClock_DIV_INT_SHIFT  (8u)

#else 

#define SPI_FastClock_DIV_REG        (*(reg32 *)SPI_FastClock__REGISTER)
#define SPI_FastClock_ENABLE_REG     SPI_FastClock_DIV_REG
#define SPI_FastClock_DIV_FRAC_MASK  SPI_FastClock__FRAC_MASK
#define SPI_FastClock_DIV_FRAC_SHIFT (16u)
#define SPI_FastClock_DIV_INT_MASK   SPI_FastClock__DIVIDER_MASK
#define SPI_FastClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SPI_FastClock_H) */

/* [] END OF FILE */
