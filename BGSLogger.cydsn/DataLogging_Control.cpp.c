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

#include <DataLogging_Control.h>
#include <main.h>
#include <FileFormat_Raw.h>
#include <FileFormat_CSV.h>
#include <Settings_Persist.h>
#include <SD.h>

uint8 filetype_ = FILETYPE_CSV;
uint32 sample_delay_ = 1000;

void DataLogging_SetFormat(uint8 format){
    filetype_ = format;
}

uint8 DataLogging_GetFormat(){
    return filetype_;
}

uint32 DataLogging_GetSampleDelay(){
    return sample_delay_;
}

void DataLogging_SetSampleDelay(uint32 tmp){
    if(tmp >= 100){
        sample_delay_ = tmp;
    }
}

void DataLogging_SetSampleDelay_Raw(uint8* buf, uint8 len){
    if(len==4){
        uint32 tmp = (buf[0]<<24) + (buf[1]<<16) + (buf[2]<<8) + buf[3];
        DataLogging_SetSampleDelay(tmp);
    }
}

void DataLogging_Start(){
    if(bLogging) return;
    switch(filetype_){
        case FILETYPE_RAW:
            Datafile_Open_Raw();
            break;
        case FILETYPE_CSV:
            Datafile_Open_CSV();
            break;
    }
    bLogging = 1;
    SD_LED_R_Write(0); // Write to the status LED
}

void DataLogging_Stop(){
    bLogging = 0;
    SD_LED_R_Write(1); // Write to the status LED
}

void DataLogging_Write(uint16 *data){
    switch(filetype_){
        case FILETYPE_RAW:
            Datafile_Write_Raw(data);
            break;
        case FILETYPE_CSV:
            Datafile_Write_CSV(data);
            break;
    }
}

void DataLogging_GetNewFileName(char *name, char ending[]){
    uint8 i = 0;
    for(sprintf(name, "LOG.%s", ending); SD.exists(name); sprintf(name, "LOG%d.%s", i, ending)){
        i++;
    }
}

/* [] END OF FILE */
