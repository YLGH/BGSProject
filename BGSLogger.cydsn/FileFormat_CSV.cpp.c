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

#include <FileFormat_CSV.h>
#include <datafile.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>

void Datafile_Write_CSV(uint16 *data){
    char str[40];
    uint32 m = (data[0] << 16) + data[1];
    uint8 i=0;
    sprintf(str, "%lu", m);
    dataFile.print(str);
    for(i=0;i<4;i++){
        if(Sensor_IsEnabled(i)){
            sprintf(str, ",%d", data[i+2]);
            dataFile.print(str);
        }
    }
    dataFile.println();
}

void Datafile_Open_CSV(){
    char name[12];
    DataLogging_GetNewFileName(name, "CSV");
    dataFile = SD.open(name, FILE_WRITE);
    dataFile.print("Time");
    uint8 i=0;
    for(i=0;i<4;i++){
        if(Sensor_IsEnabled(i)){
            dataFile.print(",\""); // Wrap names in quotes
            dataFile.print(Sensor_Names[i]);
            dataFile.print("\"");
        }
    }
    dataFile.println();
}

/* [] END OF FILE */
