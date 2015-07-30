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

#include <RTC_Control.h>
#include <stdio.h>

#define DS1307_ADDRESS 0b01101000

uint32 RTC_MostRecentTime = 0;

uint8 isLeapYear(uint8 year){
    uint16 tmpYear = 2000 + year;
    if ((tmpYear%4) != 0) return 0;
    if ((tmpYear%100) != 0) return 1;
    if ((tmpYear%400) == 0) return 1;
    return 0;
}

uint8 RTC_Set(tm_elems *tm){
    uint8 buf[8];
    buf[0] = 0x00; // first byte is address
    buf[1] = ((tm->seconds / 10) << 4) | (tm->seconds % 10);
    buf[2] = ((tm->minutes / 10) << 4) | (tm->minutes % 10);
    buf[3] = ((tm->hours / 10) << 4) | (tm->hours % 10);
    buf[4] = tm->dow;
    buf[5] = ((tm->date / 10) << 4) | (tm->date % 10);
    buf[6] = ((tm->month / 10) << 4) | (tm->month % 10);
    buf[7] = ((tm->year / 10) << 4) | (tm->year % 10);
    
    I2C_RTC_I2CMasterClearStatus();
    I2C_RTC_I2CMasterWriteBuf(DS1307_ADDRESS, buf, sizeof(buf), I2C_RTC_I2C_MODE_COMPLETE_XFER);
    while(0 == (I2C_RTC_I2CMasterStatus() & I2C_RTC_I2C_MSTAT_WR_CMPLT)){
        // Wait for write to complete
    }
    return 1;
}

uint8 RTC_Get(tm_elems *tm){
    
    uint32 err = I2C_RTC_I2CMasterSendStart(DS1307_ADDRESS, I2C_RTC_I2C_WRITE_XFER_MODE);
    if(err!=I2C_RTC_I2C_MSTR_NO_ERROR){
        return 0;
    }
    I2C_RTC_I2CMasterWriteByte(0x00);
    I2C_RTC_I2CMasterSendStop();
    
    uint8 buf[7];
    I2C_RTC_I2CMasterClearStatus();
    I2C_RTC_I2CMasterReadBuf(DS1307_ADDRESS, buf, sizeof(buf), I2C_RTC_I2C_MODE_COMPLETE_XFER);
    
    while(0 == (I2C_RTC_I2CMasterStatus() & I2C_RTC_I2C_MSTAT_RD_CMPLT)){
        // Wait for read to complete
    }
    
    tm->seconds = (((buf[0] & 0x70)>>4)*10) + (buf[0] & 0x0F);
    tm->minutes = (((buf[1] & 0x70)>>4)*10) + (buf[1] & 0x0F);
    tm->hours = (((buf[2] & 0x30)>>4)*10) + (buf[2] & 0x0F);
    tm->dow = buf[3] & 0x07;
    tm->date = (((buf[4] & 0x30)>>4)*10) + (buf[4] & 0x0F);
    tm->month = (((buf[5] & 0x10)>>4)*10) + (buf[5] & 0x0F);
    tm->year = (((buf[6] & 0xF0)>>4)*10) + (buf[6] & 0x0F);
    
    return 1;
}

void RTC_TimeFromUnix(tm_elems *tm, uint32 timestamp){
    tm->year = (timestamp / 31536000) - 30;
    uint8 numLeapYears = ((2000+tm->year)-1969)/4;
    uint16 numDays = (timestamp / 86400);
    uint16 daysThisYear = (numDays - numLeapYears) % 365;
    if(isLeapYear(tm->year) && daysThisYear>59) daysThisYear++;
    uint8 i = 0;
    for(i=0;i<sizeof(RTC_DAYS_IN_MONTH);i++){
        if(daysThisYear <= RTC_DAYS_IN_MONTH[i]) break;
        daysThisYear -= RTC_DAYS_IN_MONTH[i];
    }
    tm->date = daysThisYear+1;
    tm->month = i+1;
    uint32 secsThisDay = timestamp - (numDays * 86400);
    tm->hours = secsThisDay / 3600;
    uint16 minutesLeft = secsThisDay - (tm->hours * 3600);
    tm->minutes = minutesLeft/60;
    tm->seconds = minutesLeft - (tm->minutes * 60);
    tm->dow = (numDays+4)%7;
}

void RTC_PrintTime(tm_elems *tm){
    char uart_str[30];
    uint32 ts = RTC_UnixFromTime(tm);
    sprintf(uart_str, "Time is: %s %d/%d/%d %d:%d:%d\n\r", RTC_DAY_NAMES[tm->dow], tm->date, tm->month, tm->year, tm->hours, tm->minutes, tm->seconds);
    UART_UartPutString(uart_str);
    sprintf(uart_str, "This is UNIX time: %lu\n\r", ts);
    UART_UartPutString(uart_str);
}

void RTC_Start(){
    I2C_RTC_Start();
}

uint32 RTC_UnixFromTime(tm_elems *tm){
    uint32 timestamp = 0;
    uint8 numYears = (2000 + tm->year)-1970;
    uint8 numLeapYears = numYears / 4;
    uint16 numDays = numYears * 365;
    numDays += numLeapYears;
    uint8 i = 0;
    if(isLeapYear(tm->year) && tm->month>2) numDays += 1;
    for(i=0; i < (tm->month-1); i++){
        numDays += RTC_DAYS_IN_MONTH[i];
    }
    numDays += (tm->date-1);
    timestamp = numDays * 86400;
    timestamp += (tm->hours * 3600);
    timestamp += (tm->minutes * 60);
    timestamp += (tm->seconds);
    return timestamp;
}

int32 RTC_TimeDifference(tm_elems *tm1, tm_elems *tm2){
    uint32 ts1 = RTC_UnixFromTime(tm1);
    uint32 ts2 = RTC_UnixFromTime(tm2);
    if(ts1>ts2) return -1;
    return ts2 - ts1;
}

uint8 RTC_Equals(tm_elems *tm1, tm_elems *tm2){
    return tm1->year==tm2->year && tm1->month==tm2->month && tm1->date==tm2->date
        && tm1->hours==tm2->hours && tm1->minutes==tm2->minutes && tm1->seconds==tm2->seconds;
}

/* [] END OF FILE */
