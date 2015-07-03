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
#include <project.h>
#include <main.h>
#include <stdio.h>

uint32 timeChan[4];

uint8 timesValid = 0;

char uartString[0x40] = {' '};

int main()
{
    /* INITIALIZE EVERTHING */
    
    // ADC
    ADC_Start();
    ADC_StartConvert();
    ADC_IRQ_Enable();
    
    // UART
    UART_Start();
    
    CyGlobalIntEnable;      /* Enable global interrupts */
    
    /* END INIT BLOCK */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        /* Place your application code here */
		if(timesValid){
            
            //*
            sprintf(uartString, "%lu", timeChan[0]);
            UART_UartPutString(uartString);
            
            sprintf(uartString, " ");
	    	UART_UartPutString(uartString);
            
            sprintf(uartString, "%lu", timeChan[1]);
            UART_UartPutString(uartString);
            
            sprintf(uartString, " ");
	    	UART_UartPutString(uartString);
            
            sprintf(uartString, "%lu", timeChan[2]);
            UART_UartPutString(uartString);
            sprintf(uartString, " ");
	    	UART_UartPutString(uartString);
            
            sprintf(uartString, "%lu", timeChan[3]);
            UART_UartPutString(uartString);
            //*/
            
            UART_UartPutString("\n\r");
            
            timesValid = 0;
        }
    }
}