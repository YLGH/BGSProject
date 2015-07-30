/*******************************************************************************
* File Name: SD_MOSI.h  
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

#if !defined(CY_PINS_SD_MOSI_H) /* Pins SD_MOSI_H */
#define CY_PINS_SD_MOSI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SD_MOSI_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SD_MOSI_Write(uint8 value) ;
void    SD_MOSI_SetDriveMode(uint8 mode) ;
uint8   SD_MOSI_ReadDataReg(void) ;
uint8   SD_MOSI_Read(void) ;
uint8   SD_MOSI_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SD_MOSI_DRIVE_MODE_BITS        (3)
#define SD_MOSI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SD_MOSI_DRIVE_MODE_BITS))

#define SD_MOSI_DM_ALG_HIZ         (0x00u)
#define SD_MOSI_DM_DIG_HIZ         (0x01u)
#define SD_MOSI_DM_RES_UP          (0x02u)
#define SD_MOSI_DM_RES_DWN         (0x03u)
#define SD_MOSI_DM_OD_LO           (0x04u)
#define SD_MOSI_DM_OD_HI           (0x05u)
#define SD_MOSI_DM_STRONG          (0x06u)
#define SD_MOSI_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SD_MOSI_MASK               SD_MOSI__MASK
#define SD_MOSI_SHIFT              SD_MOSI__SHIFT
#define SD_MOSI_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SD_MOSI_PS                     (* (reg32 *) SD_MOSI__PS)
/* Port Configuration */
#define SD_MOSI_PC                     (* (reg32 *) SD_MOSI__PC)
/* Data Register */
#define SD_MOSI_DR                     (* (reg32 *) SD_MOSI__DR)
/* Input Buffer Disable Override */
#define SD_MOSI_INP_DIS                (* (reg32 *) SD_MOSI__PC2)


#if defined(SD_MOSI__INTSTAT)  /* Interrupt Registers */

    #define SD_MOSI_INTSTAT                (* (reg32 *) SD_MOSI__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SD_MOSI_DRIVE_MODE_SHIFT       (0x00u)
#define SD_MOSI_DRIVE_MODE_MASK        (0x07u << SD_MOSI_DRIVE_MODE_SHIFT)


#endif /* End Pins SD_MOSI_H */


/* [] END OF FILE */
