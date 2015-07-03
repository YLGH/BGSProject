/*******************************************************************************
* File Name: PIN_CMP_NEG.h  
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

#if !defined(CY_PINS_PIN_CMP_NEG_H) /* Pins PIN_CMP_NEG_H */
#define CY_PINS_PIN_CMP_NEG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN_CMP_NEG_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_CMP_NEG_Write(uint8 value) ;
void    PIN_CMP_NEG_SetDriveMode(uint8 mode) ;
uint8   PIN_CMP_NEG_ReadDataReg(void) ;
uint8   PIN_CMP_NEG_Read(void) ;
uint8   PIN_CMP_NEG_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_CMP_NEG_DRIVE_MODE_BITS        (3)
#define PIN_CMP_NEG_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN_CMP_NEG_DRIVE_MODE_BITS))

#define PIN_CMP_NEG_DM_ALG_HIZ         (0x00u)
#define PIN_CMP_NEG_DM_DIG_HIZ         (0x01u)
#define PIN_CMP_NEG_DM_RES_UP          (0x02u)
#define PIN_CMP_NEG_DM_RES_DWN         (0x03u)
#define PIN_CMP_NEG_DM_OD_LO           (0x04u)
#define PIN_CMP_NEG_DM_OD_HI           (0x05u)
#define PIN_CMP_NEG_DM_STRONG          (0x06u)
#define PIN_CMP_NEG_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN_CMP_NEG_MASK               PIN_CMP_NEG__MASK
#define PIN_CMP_NEG_SHIFT              PIN_CMP_NEG__SHIFT
#define PIN_CMP_NEG_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_CMP_NEG_PS                     (* (reg32 *) PIN_CMP_NEG__PS)
/* Port Configuration */
#define PIN_CMP_NEG_PC                     (* (reg32 *) PIN_CMP_NEG__PC)
/* Data Register */
#define PIN_CMP_NEG_DR                     (* (reg32 *) PIN_CMP_NEG__DR)
/* Input Buffer Disable Override */
#define PIN_CMP_NEG_INP_DIS                (* (reg32 *) PIN_CMP_NEG__PC2)


#if defined(PIN_CMP_NEG__INTSTAT)  /* Interrupt Registers */

    #define PIN_CMP_NEG_INTSTAT                (* (reg32 *) PIN_CMP_NEG__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN_CMP_NEG_DRIVE_MODE_SHIFT       (0x00u)
#define PIN_CMP_NEG_DRIVE_MODE_MASK        (0x07u << PIN_CMP_NEG_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN_CMP_NEG_H */


/* [] END OF FILE */
