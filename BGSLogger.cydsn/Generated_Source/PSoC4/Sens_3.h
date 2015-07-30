/*******************************************************************************
* File Name: Sens_3.h  
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

#if !defined(CY_PINS_Sens_3_H) /* Pins Sens_3_H */
#define CY_PINS_Sens_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Sens_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Sens_3_Write(uint8 value) ;
void    Sens_3_SetDriveMode(uint8 mode) ;
uint8   Sens_3_ReadDataReg(void) ;
uint8   Sens_3_Read(void) ;
uint8   Sens_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sens_3_DRIVE_MODE_BITS        (3)
#define Sens_3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Sens_3_DRIVE_MODE_BITS))

#define Sens_3_DM_ALG_HIZ         (0x00u)
#define Sens_3_DM_DIG_HIZ         (0x01u)
#define Sens_3_DM_RES_UP          (0x02u)
#define Sens_3_DM_RES_DWN         (0x03u)
#define Sens_3_DM_OD_LO           (0x04u)
#define Sens_3_DM_OD_HI           (0x05u)
#define Sens_3_DM_STRONG          (0x06u)
#define Sens_3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Sens_3_MASK               Sens_3__MASK
#define Sens_3_SHIFT              Sens_3__SHIFT
#define Sens_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sens_3_PS                     (* (reg32 *) Sens_3__PS)
/* Port Configuration */
#define Sens_3_PC                     (* (reg32 *) Sens_3__PC)
/* Data Register */
#define Sens_3_DR                     (* (reg32 *) Sens_3__DR)
/* Input Buffer Disable Override */
#define Sens_3_INP_DIS                (* (reg32 *) Sens_3__PC2)


#if defined(Sens_3__INTSTAT)  /* Interrupt Registers */

    #define Sens_3_INTSTAT                (* (reg32 *) Sens_3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Sens_3_DRIVE_MODE_SHIFT       (0x00u)
#define Sens_3_DRIVE_MODE_MASK        (0x07u << Sens_3_DRIVE_MODE_SHIFT)


#endif /* End Pins Sens_3_H */


/* [] END OF FILE */
