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

#ifdef __cplusplus
    extern "C"{
#endif
    #include <project.h>
#ifdef __cplusplus
    }
#endif

#define FILETYPE_RAW 0x01
#define FILETYPE_CSV 0x02

void DataLogging_SetFormat(uint8 format);

uint8 DataLogging_GetFormat();

void DataLogging_SetSampleDelay(uint32 delay);
void DataLogging_SetSampleDelay_Raw(uint8* buf, uint8 len);
uint32 DataLogging_GetSampleDelay();

void DataLogging_Start();
void DataLogging_Stop();

void DataLogging_Write(uint16 data[]);

void DataLogging_GetNewFileName(char *name, char ending[]);

/* [] END OF FILE */
