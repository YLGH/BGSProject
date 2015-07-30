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

#include <SD.h>
#include <Settings_Persist.h>
#include <DataLogging_Control.h>
#include <SD_Control.h>
#include <Sensor_Control.h>
#include <Settings_FileRead.h>
#include <Scheduling.h>

#define FLASH_ROW_SIZE_BYTES    128
#define FLASH_ALIGNED           __attribute__ ((aligned (FLASH_ROW_SIZE_BYTES)))

static const uint8 FLASH_ALIGNED flashRowDataFLASH[FLASH_ROW_SIZE_BYTES] = {0};

#define FLASH_DATA_BASE_ADDRESS_BYTE    (uint32) (&flashRowDataFLASH)
#define FLASH_DATA_BASE_ADDRESS_ROW     FLASH_DATA_BASE_ADDRESS_BYTE / FLASH_ROW_SIZE_BYTES

uint8 flashRowDataSRAM[FLASH_ROW_SIZE_BYTES] = {0};

File configFile;

uint8 Settings_LoadFromCard(){
    if(SD_IsCardReady()){
        if(SD.exists("config.txt")){
            configFile = SD.open("config.txt", FILE_READ);
            uint8 buf[32];
            uint8 nread = configFile.read(buf, sizeof(buf));
            while(nread>0){
                Settings_ProcessBuffer(buf, nread);
                nread = configFile.read(buf, sizeof(buf));
            }
            buf[0] = '\n';
            Settings_ProcessBuffer(buf, 1);
            configFile.close();
            Settings_Save();
            return 1;
        }
    }
    return 0;
}

uint32 get_int32(uint8 idx){
    return (flashRowDataSRAM[idx]<<24) + (flashRowDataSRAM[idx+1]<<16) + (flashRowDataSRAM[idx+2]<<8) + flashRowDataSRAM[idx+3];
}

void Settings_Load(){
    uint8 i = 0;
    for(i=0;i<FLASH_ROW_SIZE_BYTES;i++){
        flashRowDataSRAM[i] = flashRowDataFLASH[i];
    }
    if(flashRowDataSRAM[127]){ // Presence byte
        for(i=0;i<80;i++){
            Sensor_Names[i/20][i%20] = flashRowDataSRAM[i];
        }
        DataLogging_SetFormat(flashRowDataSRAM[80]);
        
        DataLogging_SetSampleDelay(get_int32(81));
        
        Sensors_Enabled = flashRowDataSRAM[85];
        
        Scheduling_SetStartTimeUnix(get_int32(86));
        Scheduling_SetEndTimeUnix(get_int32(90));
        if(flashRowDataSRAM[94]){
            Scheduling_Enable();
        }else{
            Scheduling_Disable();
        }
    }
}

void store_int32(uint8 idx, uint32 val){
    flashRowDataSRAM[idx] = (val >> 24) & 0xFF;
    flashRowDataSRAM[idx+1] = (val >> 16) & 0xFF;
    flashRowDataSRAM[idx+2] = (val >> 8) & 0xFF;
    flashRowDataSRAM[idx+3] = val & 0xFF;
}

uint8 Settings_Save(){
    CySysFlashSetWaitCycles(48);
    
    uint8 i = 0;
    for(i=0;i<80;i++){
        flashRowDataSRAM[i] = Sensor_Names[i/20][i%20];
    }
    flashRowDataSRAM[80] = DataLogging_GetFormat();
    
    store_int32(81, DataLogging_GetSampleDelay());
    
    flashRowDataSRAM[85] = Sensors_Enabled;
    
    store_int32(86, Scheduling_GetStartTimeUnix());
    store_int32(90, Scheduling_GetEndTimeUnix());
    flashRowDataSRAM[94] = Scheduling_IsEnabled();
    
    flashRowDataSRAM[127] = 1; // Presence byte
    
    return CySysFlashWriteRow(FLASH_DATA_BASE_ADDRESS_ROW, flashRowDataSRAM);
}

/* [] END OF FILE */
