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

#include <FileFormat_Raw.h>
#include <datafile.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>

void Datafile_Write_Raw(uint16 *data){
    uint8 i = 0;
    for(i=0;i<6;i++){
        if(i<2 || Sensor_IsEnabled(i-2)){
            uint16 val = data[i];
            dataFile.write((val>>8)&0xFF);
            dataFile.write(val & 0xFF);
        }
    }
}

void Datafile_Open_Raw(){
    char name[12];
    DataLogging_GetNewFileName(name, "BIN");
    dataFile = SD.open(name, FILE_WRITE);
    uint8 i = 0;
    uint8 j = 0;
    dataFile.write(Sensors_Enabled);
    for(i=0;i<4;i++){
        if(Sensor_IsEnabled(i)){
            for(j=0;j<20;j++){
                dataFile.write(Sensor_Names[i][j]);
            }
        }
    }
}

/* [] END OF FILE */
