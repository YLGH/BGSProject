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

#include <SD_Control.h>
#include <SD.h>

uint8 cardReady_ = 0;

uint8 SD_Connect(){
    
    uint8 retVal = 1;
    
    Clock_SD_SPI_SetDivider(63); // Set the clock down to 375kHz for card init
    
    // Connect to SD Card
    if(!SD.begin()){
        retVal = 0;
    }
    
    Clock_SD_SPI_SetDivider(1); // Set the clock back to 24MHz
    
    cardReady_ = retVal;
    
    return retVal;
}

uint8 SD_IsCardReady(){
    return cardReady_;
}

/* [] END OF FILE */
