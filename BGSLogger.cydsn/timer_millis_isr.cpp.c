/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <timer_millis_isr.h>
#include <main.h>
#include <DataLogging_Control.h>
#include <Scheduling.h>

uint16 subcount_ = 0;
uint32 logintervalcount_ = 0;

CY_ISR(TIMER_MILLIS_CPP_ISR){
    
    subcount_++;
    if(subcount_>=100){
        subcount_ = 0;
        millis_++;
        if((millis_%1000)==0){
            FLAG_SCHEDULING_CHECK = 1;
        }
    }
    
    if(bLogging){
        logintervalcount_ ++;
        if (logintervalcount_ >= DataLogging_GetSampleDelay()){
            logintervalcount_ = 0;
            bTimeToLog = 0x01;
        }
    }
}

/* [] END OF FILE */
