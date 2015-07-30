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

#include <btn_startstop_isr.h>
#include <main.h>
#include <DataLogging_Control.h>

uint32 lastPressedTime = 0;

CY_ISR(BUTTON_STARTSTOP_CPP_ISR){
    
    if((millis_ - lastPressedTime) > 500){
        if(bLogging){
            DataLogging_Stop();
        }else{
            DataLogging_Start();
        }
    }
    lastPressedTime = millis_;
    Button_Stop_ClearInterrupt();
    
}

/* [] END OF FILE */
