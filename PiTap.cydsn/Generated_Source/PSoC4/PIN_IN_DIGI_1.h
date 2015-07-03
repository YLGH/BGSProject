/*******************************************************************************
* File Name: PIN_IN_DIGI_1.h  
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

#if !defined(CY_PINS_PIN_IN_DIGI_1_H) /* Pins PIN_IN_DIGI_1_H */
#define CY_PINS_PIN_IN_DIGI_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN_IN_DIGI_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_IN_DIGI_1_Write(uint8 value) ;
void    PIN_IN_DIGI_1_SetDriveMode(uint8 mode) ;
uint8   PIN_IN_DIGI_1_ReadDataReg(void) ;
uint8   PIN_IN_DIGI_1_Read(void) ;
uint8   PIN_IN_DIGI_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_IN_DIGI_1_DRIVE_MODE_BITS        (3)
#define PIN_IN_DIGI_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN_IN_DIGI_1_DRIVE_MODE_BITS))

#define PIN_IN_DIGI_1_DM_ALG_HIZ         (0x00u)
#define PIN_IN_DIGI_1_DM_DIG_HIZ         (0x01u)
#define PIN_IN_DIGI_1_DM_RES_UP          (0x02u)
#define PIN_IN_DIGI_1_DM_RES_DWN         (0x03u)
#define PIN_IN_DIGI_1_DM_OD_LO           (0x04u)
#define PIN_IN_DIGI_1_DM_OD_HI           (0x05u)
#define PIN_IN_DIGI_1_DM_STRONG          (0x06u)
#define PIN_IN_DIGI_1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN_IN_DIGI_1_MASK               PIN_IN_DIGI_1__MASK
#define PIN_IN_DIGI_1_SHIFT              PIN_IN_DIGI_1__SHIFT
#define PIN_IN_DIGI_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_IN_DIGI_1_PS                     (* (reg32 *) PIN_IN_DIGI_1__PS)
/* Port Configuration */
#define PIN_IN_DIGI_1_PC                     (* (reg32 *) PIN_IN_DIGI_1__PC)
/* Data Register */
#define PIN_IN_DIGI_1_DR                     (* (reg32 *) PIN_IN_DIGI_1__DR)
/* Input Buffer Disable Override */
#define PIN_IN_DIGI_1_INP_DIS                (* (reg32 *) PIN_IN_DIGI_1__PC2)


#if defined(PIN_IN_DIGI_1__INTSTAT)  /* Interrupt Registers */

    #define PIN_IN_DIGI_1_INTSTAT                (* (reg32 *) PIN_IN_DIGI_1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN_IN_DIGI_1_DRIVE_MODE_SHIFT       (0x00u)
#define PIN_IN_DIGI_1_DRIVE_MODE_MASK        (0x07u << PIN_IN_DIGI_1_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN_IN_DIGI_1_H */


/* [] END OF FILE */
