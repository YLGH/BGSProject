/*******************************************************************************
* File Name: Pin_Debug4.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_Debug4_H) /* Pins Pin_Debug4_H */
#define CY_PINS_Pin_Debug4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_Debug4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_Debug4_Write(uint8 value) ;
void    Pin_Debug4_SetDriveMode(uint8 mode) ;
uint8   Pin_Debug4_ReadDataReg(void) ;
uint8   Pin_Debug4_Read(void) ;
uint8   Pin_Debug4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_Debug4_DRIVE_MODE_BITS        (3)
#define Pin_Debug4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_Debug4_DRIVE_MODE_BITS))

#define Pin_Debug4_DM_ALG_HIZ         (0x00u)
#define Pin_Debug4_DM_DIG_HIZ         (0x01u)
#define Pin_Debug4_DM_RES_UP          (0x02u)
#define Pin_Debug4_DM_RES_DWN         (0x03u)
#define Pin_Debug4_DM_OD_LO           (0x04u)
#define Pin_Debug4_DM_OD_HI           (0x05u)
#define Pin_Debug4_DM_STRONG          (0x06u)
#define Pin_Debug4_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin_Debug4_MASK               Pin_Debug4__MASK
#define Pin_Debug4_SHIFT              Pin_Debug4__SHIFT
#define Pin_Debug4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_Debug4_PS                     (* (reg32 *) Pin_Debug4__PS)
/* Port Configuration */
#define Pin_Debug4_PC                     (* (reg32 *) Pin_Debug4__PC)
/* Data Register */
#define Pin_Debug4_DR                     (* (reg32 *) Pin_Debug4__DR)
/* Input Buffer Disable Override */
#define Pin_Debug4_INP_DIS                (* (reg32 *) Pin_Debug4__PC2)


#if defined(Pin_Debug4__INTSTAT)  /* Interrupt Registers */

    #define Pin_Debug4_INTSTAT                (* (reg32 *) Pin_Debug4__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin_Debug4_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_Debug4_DRIVE_MODE_MASK        (0x07u << Pin_Debug4_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin_Debug4_H */


/* [] END OF FILE */
