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

extern uint8 FLAG_SCHEDULING_CHECK;

#include <RTC_Control.h>

void Scheduling_SetStartTimeUnix(uint32 ts);
void Scheduling_SetEndTimeUnix(uint32 ts);
uint32 Scheduling_GetStartTimeUnix();
uint32 Scheduling_GetEndTimeUnix();
void Scheduling_Enable();
void Scheduling_Disable();
uint8 Scheduling_IsEnabled();
uint8 Scheduling_Check();

/* [] END OF FILE */
