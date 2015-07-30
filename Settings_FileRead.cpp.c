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

#include <Settings_FileRead.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>
#include <Scheduling.h>
#include <stdlib.h>

#define STATE_IN_KEY 1
#define STATE_WAITING_VALUE 2
#define STATE_IN_VALUE 3
#define STATE_WAITING_KEY 4
#define STATE_IN_COMMENT 5

/* Keys:
 * channel_x_name <1-20 chars>
 * channel_x_enabled <0/1>
 * sample_delay <100-4294967295>
 * file_format <raw/csv>
 * start_time yyyy-mm-dd hh:mm:ss
 * end_time yyyy-mm-dd hh:mm:ss
 */

const uint8 STR_CHANNEL_x_NAME[] = {'c','h','a','n','n','e','l','_',1,'_','n','a','m','e',};
const uint8 STR_CHANNEL_x_ENABLED[] = {'c','h','a','n','n','e','l','_',1,'_','e','n','a','b','l','e','d'};
const uint8 STR_DATE_FORMAT[] = {1,1,1,1,'-',1,1,'-',1,1,' ',1,1,':',1,1,':',1,1};
const uint8 STR_SAMPLE_DELAY[] = "sample_delay";
const uint8 STR_FILE_FORMAT[] = "file_format";
const uint8 STR_START_TIME[] = "start_time";
const uint8 STR_END_TIME[] = "end_time";
const uint8 STR_TRUE[] = "true";
const uint8 STR_FALSE[] = "false";
const uint8 STR_YES[] = "yes";
const uint8 STR_NO[] = "no";
const uint8 STR_RAW[] = "raw";
const uint8 STR_CSV[] = "csv";

char key[20];
char value[20];
uint8 state = STATE_WAITING_KEY;
uint8 keylen = 0;
uint8 valuelen = 0;

uint8 is_number(uint8 c){
    return (c>='0' && c<='9');
}

uint8 is_alpha(uint8 c){  
    return (c>='0' && c<='9') || (c>='A' && c<='Z') || (c>='a' && c<='z') || (c=='_');
}

uint8 matches(char st1[], const uint8 st2[], uint8 len){
    uint8 i = 0;
    for(i=0;i<len;i++){
        if(!(st2[i]==1 && is_number(st1[i])) && !(st2[i]==st1[i] || st2[i]==(st1[i]+32))) return 0;
    }
    return 1;
}

void process_channel_enabled(uint8 idx){
    if(valuelen==1){
        if(value[0]=='1'){
            Sensor_Enable(idx);
        }else if(value[0]=='0'){
            Sensor_Disable(idx);
        }
    }else if(valuelen==2){
        if(matches(value, STR_NO, valuelen)) Sensor_Disable(idx);
    }else if(valuelen==3){
        if(matches(value, STR_YES, valuelen)) Sensor_Enable(idx);
    }else if(valuelen==4){
        if(matches(value, STR_TRUE, valuelen)) Sensor_Enable(idx);
    }else if(valuelen==5){
        if(matches(value, STR_FALSE, valuelen)) Sensor_Disable(idx);
    }
}

void process_channel_name(uint8 idx){
    Sensor_SetName(idx, value, valuelen);
}

void process_sample_delay(){
    DataLogging_SetSampleDelay(atoi(value));
}

void process_file_format(){
    if(valuelen==3){
        if(matches(value, STR_RAW, valuelen)){
            DataLogging_SetFormat(FILETYPE_RAW);
        }else if(matches(value, STR_CSV, valuelen)){
            DataLogging_SetFormat(FILETYPE_CSV);
        }
    }
}

void read_time(tm_elems *tm){
    char sYear[4];
    char sMonth[2];
    char sDate[2];
    char sHour[2];
    char sMinute[2];
    char sSecond[2];
    uint8 i = 0;
    for(i=0;i<4;i++){ sYear[i] = value[i]; }
    for(i=0;i<2;i++){ sMonth[i] = value[i+5]; }
    for(i=0;i<2;i++){ sDate[i] = value[i+8]; }
    for(i=0;i<2;i++){ sHour[i] = value[i+11]; }
    for(i=0;i<2;i++){ sMinute[i] = value[i+14]; }
    for(i=0;i<2;i++){ sSecond[i] = value[i+17]; }
    tm->year = (atoi(sYear)-2000);
    tm->month = atoi(sMonth);
    tm->date = atoi(sDate);
    tm->hours = atoi(sHour);
    tm->minutes = atoi(sMinute);
    tm->seconds = atoi(sSecond);
}

void process_start_time(){
    if(!matches(value, STR_DATE_FORMAT, valuelen)) return;
    tm_elems tm;
    read_time(&tm);
    Scheduling_SetStartTimeUnix(RTC_UnixFromTime(&tm));
}

void process_end_time(){
    if(!matches(value, STR_DATE_FORMAT, valuelen)) return;
    tm_elems tm;
    read_time(&tm);
    Scheduling_SetEndTimeUnix(RTC_UnixFromTime(&tm));
    Scheduling_Enable();
}

void process_keyvalue(){
    if(keylen==17){
        if(!matches(key, STR_CHANNEL_x_ENABLED, keylen)) return;
        process_channel_enabled(key[8]-48 - 1);
    }else if(keylen==14){
        if(!matches(key, STR_CHANNEL_x_NAME, keylen)) return;
        process_channel_name(key[8]-48 - 1);
    }else if(keylen==12){
        if(!matches(key, STR_SAMPLE_DELAY, keylen)) return;
        process_sample_delay();
    }else if(keylen==11){
        if(!matches(key, STR_FILE_FORMAT, keylen)) return;
        process_file_format();
    }else if(keylen==10){
        if(!matches(key, STR_START_TIME, keylen)) return;
        process_start_time();
    }else if(keylen==8){
        if(!matches(key, STR_END_TIME, keylen)) return;
        process_end_time();
    }
}

void process_char(uint8 c){
    if(c=='\n' || c == '\r'){
        if(keylen>0 && valuelen>0) process_keyvalue();
        keylen = valuelen = 0;
        state = STATE_WAITING_KEY;
    }else{
        if(state == STATE_WAITING_KEY){
            if(c=='#'){
                state = STATE_IN_COMMENT;
            }else if(is_alpha(c)){
                key[keylen++] = c;
                state = STATE_IN_KEY;
            }
        }else if(state == STATE_IN_KEY){
            if(is_alpha(c)){
                if(keylen<sizeof(key)) key[keylen++] = c;
            }else{
                state = STATE_WAITING_VALUE;
                valuelen = 0;
            }
        }else if(state == STATE_WAITING_VALUE){
            if(is_alpha(c)){
                value[valuelen++] = c;
                state = STATE_IN_VALUE;
            }
        }else if(state == STATE_IN_VALUE){
            if(valuelen<sizeof(value)) value[valuelen++] = c;
        }
    }
}

void Settings_ProcessBuffer(uint8 buf[], uint8 buflen){
    uint8 i = 0;
    for(i=0;i<buflen;i++){
        process_char(buf[i]);
    }
}

/* [] END OF FILE */
