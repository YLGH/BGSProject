/*******************************************************************************
* File Name: Button_Stop.h  
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

#if !defined(CY_PINS_Button_Stop_H) /* Pins Button_Stop_H */
#define CY_PINS_Button_Stop_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Button_Stop_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Stop_Write(uint8 value) ;
void    Button_Stop_SetDriveMode(uint8 mode) ;
uint8   Button_Stop_ReadDataReg(void) ;
uint8   Button_Stop_Read(void) ;
uint8   Button_Stop_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_Stop_DRIVE_MODE_BITS        (3)
#define Button_Stop_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Button_Stop_DRIVE_MODE_BITS))

#define Button_Stop_DM_ALG_HIZ         (0x00u)
#define Button_Stop_DM_DIG_HIZ         (0x01u)
#define Button_Stop_DM_RES_UP          (0x02u)
#define Button_Stop_DM_RES_DWN         (0x03u)
#define Button_Stop_DM_OD_LO           (0x04u)
#define Button_Stop_DM_OD_HI           (0x05u)
#define Button_Stop_DM_STRONG          (0x06u)
#define Button_Stop_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Button_Stop_MASK               Button_Stop__MASK
#define Button_Stop_SHIFT              Button_Stop__SHIFT
#define Button_Stop_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_Stop_PS                     (* (reg32 *) Button_Stop__PS)
/* Port Configuration */
#define Button_Stop_PC                     (* (reg32 *) Button_Stop__PC)
/* Data Register */
#define Button_Stop_DR                     (* (reg32 *) Button_Stop__DR)
/* Input Buffer Disable Override */
#define Button_Stop_INP_DIS                (* (reg32 *) Button_Stop__PC2)


#if defined(Button_Stop__INTSTAT)  /* Interrupt Registers */

    #define Button_Stop_INTSTAT                (* (reg32 *) Button_Stop__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Button_Stop_DRIVE_MODE_SHIFT       (0x00u)
#define Button_Stop_DRIVE_MODE_MASK        (0x07u << Button_Stop_DRIVE_MODE_SHIFT)


#endif /* End Pins Button_Stop_H */


/* [] END OF FILE */
