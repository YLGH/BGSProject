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

extern char Sensor_Names[][20];
extern uint8 Sensors_Enabled;

void Sensor_SetName(uint8 index, char* name, uint8 nameLen);
void Sensor_SetName_Raw(uint8* buf, uint8 len);

void Sensor_Enable(uint8 index);
void Sensor_Disable(uint8 index);

uint8 Sensor_IsEnabled(uint8 index);

/* [] END OF FILE */
