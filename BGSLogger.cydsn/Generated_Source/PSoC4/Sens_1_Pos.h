/*******************************************************************************
* File Name: Sens_1_Pos.h  
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

#if !defined(CY_PINS_Sens_1_Pos_H) /* Pins Sens_1_Pos_H */
#define CY_PINS_Sens_1_Pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Sens_1_Pos_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Sens_1_Pos_Write(uint8 value) ;
void    Sens_1_Pos_SetDriveMode(uint8 mode) ;
uint8   Sens_1_Pos_ReadDataReg(void) ;
uint8   Sens_1_Pos_Read(void) ;
uint8   Sens_1_Pos_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sens_1_Pos_DRIVE_MODE_BITS        (3)
#define Sens_1_Pos_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Sens_1_Pos_DRIVE_MODE_BITS))

#define Sens_1_Pos_DM_ALG_HIZ         (0x00u)
#define Sens_1_Pos_DM_DIG_HIZ         (0x01u)
#define Sens_1_Pos_DM_RES_UP          (0x02u)
#define Sens_1_Pos_DM_RES_DWN         (0x03u)
#define Sens_1_Pos_DM_OD_LO           (0x04u)
#define Sens_1_Pos_DM_OD_HI           (0x05u)
#define Sens_1_Pos_DM_STRONG          (0x06u)
#define Sens_1_Pos_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Sens_1_Pos_MASK               Sens_1_Pos__MASK
#define Sens_1_Pos_SHIFT              Sens_1_Pos__SHIFT
#define Sens_1_Pos_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sens_1_Pos_PS                     (* (reg32 *) Sens_1_Pos__PS)
/* Port Configuration */
#define Sens_1_Pos_PC                     (* (reg32 *) Sens_1_Pos__PC)
/* Data Register */
#define Sens_1_Pos_DR                     (* (reg32 *) Sens_1_Pos__DR)
/* Input Buffer Disable Override */
#define Sens_1_Pos_INP_DIS                (* (reg32 *) Sens_1_Pos__PC2)


#if defined(Sens_1_Pos__INTSTAT)  /* Interrupt Registers */

    #define Sens_1_Pos_INTSTAT                (* (reg32 *) Sens_1_Pos__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Sens_1_Pos_DRIVE_MODE_SHIFT       (0x00u)
#define Sens_1_Pos_DRIVE_MODE_MASK        (0x07u << Sens_1_Pos_DRIVE_MODE_SHIFT)


#endif /* End Pins Sens_1_Pos_H */


/* [] END OF FILE */
