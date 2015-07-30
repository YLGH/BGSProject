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
#include <UART_Command.h>

void uartPutArray(uint8 val[], uint32 len){
    UART_SpiUartPutArray(val, len); // This is common to SPI and UART modes
}

CY_ISR(UART_COMMAND_CPP_ISR){
    uint8 val = UART_UartGetByte();
    
    UART_INTR_RX_REG = 0xFF;
    
    Command_Process_Char(val, UART_SpiUartClearTxBuffer, UART_SpiUartWriteTxData, uartPutArray);
}

/* [] END OF FILE */
