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

#include <main.h>
#include <SD.h>
#include <adc_isr.h>
#include <btn_startstop_isr.h>
#include <timer_millis_isr.h>
#include <datafile.h>
#include <SD_Control.h>
#include <Command.h>
#include <SPI_Command.h>
#include <UART_Command.h>
#include <DataLogging_Control.h>
#include <Sensor_Control.h>
#include <Settings_Persist.h>
#include <Scheduling.h>

uint32 millis_ = 0;
uint16 aval[4];

File dataFile;

uint8 bLogging = 0;
uint8 bTimeToLog = 0;

char uart_str[40];

int main()
{   
    CyGlobalIntEnable; // Enable interrupts
    
    // Start Comms
    UART_Recv_ISR_StartEx(&UART_COMMAND_CPP_ISR);
    UART_Start();
    //SPI_Recv_ISR_StartEx(&SPI_COMMAND_CPP_ISR);
    //SPI_PI_Start();
    
    // Start the RTC
    RTC_Start();
    
    // Start the timer which tracks millis()
    Timer_Millis_ISR_StartEx(&TIMER_MILLIS_CPP_ISR);
    Timer_Millis_Start();
    
    // Start listening for button presses
    Button_Stop_ISR_StartEx(&BUTTON_STARTSTOP_CPP_ISR);
    
    // Start ADC and begin sampling
    ADC_Start();
    ADC_IRQ_StartEx(&ADC_CPP_ISR);
    ADC_StartConvert();
    
    // Connect to the SD Card
    if(SD_Connect()){
        UART_UartPutString("Found a card!\n\r");
        if(!Settings_LoadFromCard()){
            Settings_Load();
        }else{
            SD_LED_B_Write(0); // Blink blue LED to indicate successful load from card
            CyDelay(100);
            SD_LED_B_Write(1);
        }
    }else{
        UART_UartPutString("Card failed or missing!\n\r");
        Settings_Load();
    }
    
    // Start main loop
    for(;;)
    {
        if(FLAG_SCHEDULING_CHECK){
            FLAG_SCHEDULING_CHECK = 0;
            uint8 ret = Scheduling_Check();
            if(ret==1){
                COMMAND_START_LOGGING = 1;
            }else if(ret==2){
                COMMAND_STOP_LOGGING = 1;
            }
        }
        
        if(COMMAND_SET_RTC_TIME){
            tm_elems tm;
            RTC_TimeFromUnix(&tm, COMMAND_SET_RTC_TIME);
            RTC_Set(&tm);
            COMMAND_SET_RTC_TIME = 0;
        }
        if(COMMAND_SAVE_SETTINGS && !bLogging){ // Don't allow saving to EEPROM while recording
            COMMAND_SAVE_SETTINGS = 0;
            Settings_Save();
        }
        if(COMMAND_START_LOGGING){
            COMMAND_START_LOGGING = 0;
            DataLogging_Start();
        }
        if(COMMAND_STOP_LOGGING){
            COMMAND_STOP_LOGGING = 0;
            DataLogging_Stop();
        }
        if(COMMAND_INITIALIZE_CARD){
            COMMAND_INITIALIZE_CARD = 0;
            SD_Connect();
        }
        
        // While there is data in the write buffer
        while(dbufsize() >= 6){
            uint8 i = 0;
            uint16 tmp[6];
            for(i=0;i<6;i++){
                tmp[i] = dbufread();
            }
            DataLogging_Write(tmp);
        }
        
        // If we aren't logging but the file is open
        if(!bLogging && dataFile){
            UART_UartPutString("Stopping logging...\n\r");
            dataFile.close(); // Close the file and write it to the disk
        }
    }
}

/* [] END OF FILE */
