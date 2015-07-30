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

#include <adc_isr.h>
#include <main.h>

CY_ISR(ADC_CPP_ISR){
    ADC_SAR_INTR_REG = 0xFF; // clear the interrupt
    aval[0] = ADC_GetResult16(0);
    aval[1] = ADC_GetResult16(1);
    aval[2] = ADC_GetResult16(2);
    aval[3] = ADC_GetResult16(3);
    
    if(bTimeToLog){
        bTimeToLog = 0;
        if(dbufsize() < (DBUFFER_SIZE-6)){ // room for all vals
            dbufwrite((millis_>>16) & 0xFFFF);
            dbufwrite(millis_ & 0xFFFF);
            dbufwrite(aval[0]);
            dbufwrite(aval[1]);
            dbufwrite(aval[2]);
            dbufwrite(aval[3]);
        }else{
            SD_LED_B_Write(0);
        }
    }
    
}

/* [] END OF FILE */
