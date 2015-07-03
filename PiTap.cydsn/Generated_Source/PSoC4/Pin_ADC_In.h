/*******************************************************************************
* File Name: Pin_ADC_In.h  
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

#if !defined(CY_PINS_Pin_ADC_In_H) /* Pins Pin_ADC_In_H */
#define CY_PINS_Pin_ADC_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_ADC_In_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_ADC_In_Write(uint8 value) ;
void    Pin_ADC_In_SetDriveMode(uint8 mode) ;
uint8   Pin_ADC_In_ReadDataReg(void) ;
uint8   Pin_ADC_In_Read(void) ;
uint8   Pin_ADC_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_ADC_In_DRIVE_MODE_BITS        (3)
#define Pin_ADC_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_ADC_In_DRIVE_MODE_BITS))

#define Pin_ADC_In_DM_ALG_HIZ         (0x00u)
#define Pin_ADC_In_DM_DIG_HIZ         (0x01u)
#define Pin_ADC_In_DM_RES_UP          (0x02u)
#define Pin_ADC_In_DM_RES_DWN         (0x03u)
#define Pin_ADC_In_DM_OD_LO           (0x04u)
#define Pin_ADC_In_DM_OD_HI           (0x05u)
#define Pin_ADC_In_DM_STRONG          (0x06u)
#define Pin_ADC_In_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin_ADC_In_MASK               Pin_ADC_In__MASK
#define Pin_ADC_In_SHIFT              Pin_ADC_In__SHIFT
#define Pin_ADC_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_ADC_In_PS                     (* (reg32 *) Pin_ADC_In__PS)
/* Port Configuration */
#define Pin_ADC_In_PC                     (* (reg32 *) Pin_ADC_In__PC)
/* Data Register */
#define Pin_ADC_In_DR                     (* (reg32 *) Pin_ADC_In__DR)
/* Input Buffer Disable Override */
#define Pin_ADC_In_INP_DIS                (* (reg32 *) Pin_ADC_In__PC2)


#if defined(Pin_ADC_In__INTSTAT)  /* Interrupt Registers */

    #define Pin_ADC_In_INTSTAT                (* (reg32 *) Pin_ADC_In__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin_ADC_In_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_ADC_In_DRIVE_MODE_MASK        (0x07u << Pin_ADC_In_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin_ADC_In_H */


/* [] END OF FILE */
