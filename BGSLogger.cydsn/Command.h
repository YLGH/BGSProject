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

extern uint8 COMMAND_START_LOGGING;
extern uint8 COMMAND_STOP_LOGGING;
extern uint8 COMMAND_INITIALIZE_CARD;
extern uint8 COMMAND_SAVE_SETTINGS;
extern uint32 COMMAND_SET_RTC_TIME;

void Command_Process_Char(uint8 val, void clearFn(), void sendFn(uint32), void arrayFn(uint8[], uint32));

/* [] END OF FILE */
