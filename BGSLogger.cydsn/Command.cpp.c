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

#include <Command.h>

#include <DataLogging_Control.h>
#include <Sensor_Control.h>
#include <Scheduling.h>
#include <SD_Control.h>
#include <Settings_Persist.h>
#include <main.h>

uint8 VERSION[] = "v0.1";

uint8 COMMAND_START_LOGGING = 0;
uint8 COMMAND_STOP_LOGGING = 0;
uint8 COMMAND_INITIALIZE_CARD = 0;
uint8 COMMAND_SAVE_SETTINGS = 0;
uint32 COMMAND_SET_RTC_TIME = 0;

uint8 readingval_ = 0;
uint8 datalen_ = 0;
uint8 lenread_ = 0;
uint8 buf[21];
uint8 i = 0;

void Command_Process_Char(uint8 val, void clearFn(), void writeFn(uint32), void arrayFn(uint8[], uint32)){
    if(readingval_ && (lenread_ != datalen_)){
        if(lenread_==0){
            if(val < 22){
                datalen_ = val+1;
            }else{
                datalen_ = 22;
            }
            lenread_ = 1;
        }else{
            buf[lenread_-1] = val;
            lenread_++;
            if(lenread_ == datalen_){
                uint8 idx;
                uint32 ts;
                switch(readingval_){
                    case 0x02: // Set sensor name
                        Sensor_SetName_Raw(buf, datalen_-1);
                        break;
                    case 0x03: // Set sample rate
                        DataLogging_SetSampleDelay_Raw(buf, datalen_-1);
                        break;
                    case 0x12: // Get sensor name
                        clearFn();
                        idx = buf[0];
                        if(idx>=4){
                            writeFn(0xFE);
                            break;
                        }
                        uint8 dat[20];
                        for(i=0;i<20;i++){
                            dat[i] = Sensor_Names[idx][i];
                        }
                        writeFn(sizeof(dat));
                        arrayFn(dat, sizeof(dat));
                        break;
                    case 0x15: // Enable sensor
                        idx = buf[0];
                        if(idx<4){
                            Sensor_Enable(idx);
                        }
                        break;
                    case 0x16: // Disable sensor
                        idx = buf[0];
                        if(idx<4){
                            Sensor_Disable(idx);
                        }
                        break;
                    case 0x18: // Set scheduled start time
                        ts = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
                        Scheduling_SetStartTimeUnix(ts);
                        break;
                    case 0x19: // Set scheduled end time
                        ts = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
                        Scheduling_SetEndTimeUnix(ts);
                        break;
                    case 0x22: // Set RTC timestamp
                        ts = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
                        COMMAND_SET_RTC_TIME = ts;
                        break;
                }
                readingval_ = 0;
            }
        }
    }else{
        uint32 tmp = 0;        
        switch(val){
            case 0x01: // 0x01 Get current sensor values
                clearFn(); // align the data to the first byte
                writeFn((aval[0]>>8) & 0xFF);
                writeFn(aval[0] & 0xFF);
                writeFn((aval[1]>>8) & 0xFF);
                writeFn(aval[1] & 0xFF);
                writeFn((aval[2]>>8) & 0xFF);
                writeFn(aval[2] & 0xFF);
                writeFn((aval[3]>>8) & 0xFF);
                writeFn(aval[3] & 0xFF);
                break;
            case 0x02: // 0x02 Set sensor name
                readingval_ = 0x02;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x03: // 0x03 Set sample delay
                readingval_ = 0x03;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x04: // 0x04 Start logging
                COMMAND_START_LOGGING = 1;
                break;
            case 0x05: // 0x05 Stop logging
                COMMAND_STOP_LOGGING = 1;
                break;
            case 0x06: // 0x06 Initialise SD card
                COMMAND_INITIALIZE_CARD = 1;
                break;
            case 0x07: // 0x07 Is card ready?
                clearFn();
                writeFn(SD_IsCardReady());
                break;
            case 0x08: // 0x08 Set RAW File type
                DataLogging_SetFormat(FILETYPE_RAW);
                break;
            case 0x09: // 0x09 Set CSV File type
                DataLogging_SetFormat(FILETYPE_CSV);
                break;
            case 0x0A: // 0x0A-0x0F RESERVED
                break;
            case 0x11: // 0x11 Report Firmware version
                clearFn();
                writeFn(sizeof(VERSION));
                arrayFn(VERSION, sizeof(VERSION));
                break;
            case 0x12: // 0x12 Get sensor name
                readingval_ = 0x12;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x13: // 0x13 Get sample delay
                clearFn();
                tmp = DataLogging_GetSampleDelay();
                writeFn((tmp>>24) & 0xFF);
                writeFn((tmp>>16) & 0xFF);
                writeFn((tmp>>8) & 0xFF);
                writeFn(tmp & 0xFF);
                break;
            case 0x14: // 0x14 Get file format
                clearFn();
                writeFn(DataLogging_GetFormat());
                break;
            case 0x15: // Enable sensor
                readingval_ = 0x15;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x16: // Disable sensor
                readingval_ = 0x16;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x17: // Get enabled sensors
                clearFn();
                writeFn(Sensors_Enabled);
                break;
            case 0x18: // Set scheduled start time
                readingval_ = 0x18;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x19: // Set scheduled end time
                readingval_ = 0x19;
                lenread_ = 0;
                datalen_ = 22;
                break;
            case 0x20: // Enable scheduling
                Scheduling_Enable();
                break;
            case 0x21: // Disable scheduling
                Scheduling_Disable();
                break;
            case 0x22: // Set RTC timestamp
                readingval_ = 0x22;
                lenread_= 0;
                datalen_ = 22;
                break;
            case 0x23: // Get RTC timestamp
                tmp = RTC_MostRecentTime;
                clearFn();
                writeFn((tmp>>24) & 0xFF);
                writeFn((tmp>>16) & 0xFF);
                writeFn((tmp>>8) & 0xFF);
                writeFn(tmp & 0xFF);
                break;
            case 0x24: // Save settings to EEPROM
                COMMAND_SAVE_SETTINGS = 1;
                break;
            case 0x25: // Is scheduling enabled
                clearFn();
                writeFn(Scheduling_IsEnabled() ? 1 : 0);
                break;
            case 0x26: // Get scheduling start
                clearFn();
                tmp = Scheduling_GetStartTimeUnix();
                writeFn((tmp>>24) & 0xFF);
                writeFn((tmp>>16) & 0xFF);
                writeFn((tmp>>8) & 0xFF);
                writeFn(tmp & 0xFF);
                break;
            case 0x27: // Get scheduling end
                clearFn();
                tmp = Scheduling_GetEndTimeUnix();
                writeFn((tmp>>24) & 0xFF);
                writeFn((tmp>>16) & 0xFF);
                writeFn((tmp>>8) & 0xFF);
                writeFn(tmp & 0xFF);
                break;
        }
    }
}

/* [] END OF FILE */
