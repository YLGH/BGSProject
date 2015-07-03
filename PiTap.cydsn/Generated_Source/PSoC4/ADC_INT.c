/*******************************************************************************
* File Name: ADC_INT.c
* Version 2.10
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */
#include <main.h>
uint8 numTriggered = 0;

uint32 samplesSinceTriggerChan[4];

#define TIMEOUT_SAMPLES 30000

/* `#END`  */

#if(ADC_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ADC_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( ADC_ISR )
    {
        uint32 intr_status;

        /* Read interrupt status register */
        intr_status = ADC_SAR_INTR_REG;

        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
        /* `#START MAIN_ADC_ISR`  */
        
        //*
        uint8 trigChan = 4;
        uint16 res0 = (uint16) ADC_GetResult16(0);
        uint16 res1 = (uint16) ADC_GetResult16(1);
        uint16 res2 = (uint16) ADC_GetResult16(2);
        uint16 res3 = (uint16) ADC_GetResult16(3);
        if((res0 > 0x09B1 || res0 < 0x064D) && samplesSinceTriggerChan[0]>TIMEOUT_SAMPLES){
            trigChan = 0;
        }else if((res1 > 0x09B1 || res1 < 0x064D) && samplesSinceTriggerChan[1]>TIMEOUT_SAMPLES){
            trigChan = 1;
        }else if((res2 > 0x09B1 || res2 < 0x064D) && samplesSinceTriggerChan[2]>TIMEOUT_SAMPLES){
            trigChan = 2;
        }else if((res3 > 0x09B1 || res3 < 0x064D) && samplesSinceTriggerChan[3]>TIMEOUT_SAMPLES){
            trigChan = 3;
        }
        //*/
        
        //*
        if(trigChan<4 && samplesSinceTriggerChan[trigChan]>TIMEOUT_SAMPLES){
            
            Pin_Debug1_DR = (1<<trigChan);
            
            samplesSinceTriggerChan[trigChan] = 0;
            timesValid = 0;
            timeChan[trigChan] = 0;
            
            if(numTriggered==0){
                TDOA_WriteCounter(4294967295u);
                TDOA_Start();
            }else{
                timeChan[trigChan] = 4294967295u - TDOA_ReadCounter();
            }
            
            numTriggered++;
            
            if(numTriggered==4){
                TDOA_Stop();
                timesValid = 1;
            }
            
        }
        //*/
                
        //*
        samplesSinceTriggerChan[0]++;
        samplesSinceTriggerChan[1]++;
        samplesSinceTriggerChan[2]++;
        samplesSinceTriggerChan[3]++;
        
        if(samplesSinceTriggerChan[0]>TIMEOUT_SAMPLES && samplesSinceTriggerChan[1]>TIMEOUT_SAMPLES && samplesSinceTriggerChan[2]>TIMEOUT_SAMPLES && samplesSinceTriggerChan[3]>TIMEOUT_SAMPLES){
            numTriggered = 0;
        }
        //*/
        
        ADC_SAR_RANGE_INTR_REG = 0x000000FF;
        
        Pin_Debug2_DR = 0;
        
        /* `#END`  */

        /* Clear handled interrupt */
        ADC_SAR_INTR_REG = intr_status;
    }

#endif   /* End ADC_IRQ_REMOVE */


/* [] END OF FILE */
